#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "uno.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

int start_game(int num_plyrs)
{
    cout << endl << endl << "Welcome to UNO" << endl << endl;

    do
    {
        cout << "How many players will be playing? (Between 2 and 10): ";
        cin >> num_plyrs;
        cin.ignore(1000, '\n');

        if (num_plyrs < 2 || num_plyrs > 10)
            cout << "Players must be between 2 and 10" << endl;

    }while(num_plyrs < 2 || num_plyrs > 10);

    return num_plyrs;
}

void create_players(vector<Player> &players, int num_plyrs, Deck &deck)
{
    // Creating the player objects and storing them into a vector to hold the order of play
    string name;
    for (int i = 0; i < num_plyrs; i++)
    {
        cout << "Enter player " << i + 1 << "'s name: ";
        cin >> name;
        cin.ignore(1000, '\n');

        Player p(name, deck); // Create player, constructor automatically deals the player a hand from the deck

        players.push_back(p); // Add player to the vector
        print_hand(p);        // writing their initial hand to their file
    }
}

void make_discard(Deck &deck, Deck &discard, Card &dropped_c)
{
    // Getiing initial card to base play off of. Can't be an action or wild card
    dropped_c = deck.deck.back();
    // If the card is a wild card or an action card
    while(dropped_c.getNumber() == 10 || dropped_c.getNumber() == 11)
    {
        deck.shuffleDeck(); // re-shuffle
        dropped_c = deck.deck.back();
    }

    // When the intial card is not an acion or wild card we take it out from the deck and put it at the top of the discard pile
    deck.deck.pop_back();
    discard.deck.push_back(dropped_c);
}

void print_hand(const Player &p)
{
    std::ofstream file;
    file.open(p.filename);
    if (!file)
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    else
    {
        Card c;
        file.clear();
        file << "Here is " << p.name << "'s current hand:" << std::endl;
        // Not able to use get_description function since it is to write to the console and this needs to be to a user's file
        for (int i = 0; i < p.hand.hand.size(); i++)
        {
            c = p.hand.hand[i];
            file << i + 1 << ": " << c.getFname() << endl;
        }
    }
}

bool can_drop(Player &p, Deck &discard)
{
    for (int i = 0; i < p.hand.size(); i++)
    {
        // The player needs to either have the same color or number as the top of the discard pile OR have a wild card to be able to play
        if (p.hand.hand[i].getName() == discard.deck.back().getName() || p.hand.hand[i].getNumber() == discard.deck.back().getNumber() || p.hand.hand[i].getNumber() == 10 || p.hand.hand[i].getColor() == discard.deck.back().getColor())
            return true;
    }
    return false;
}

int check_card(vector<Player> &v, int cur, Deck &deck, Deck &discard, Card &c)
{
    int next = cur + 1;
    if (next >= v.size()) // To make sure next is not out of bounds
        next = 0;

    if (c.getNumber() == 10) // If it's a wild card
    {
        string nextColor;
        if (c.getName() == "Draw Four")
        {
            cout << endl << v[cur].getName() << " made " << v[next].getName() << " draw 4!" << endl;
            v[next].draw4(deck);
            nextColor = v[cur].changeColor();
            discard.deck.back().setColor(nextColor); // Change the color of the discard pile so next turn will have to match
            cout << endl << v[cur].getName() << " has changed the color to " << nextColor << endl;

            print_hand(v[next]); // Update player who drew 4 hand

            next += 1;            // Skip the next person's turn since they had to draw
            if (next >= v.size()) // To keep looping the order
                next = 0;

            return next;
        }
        else if (c.getName() == "Wild Card")
        {
            cout << endl << v[cur].getName() << " is changing the color." << endl;
            nextColor = v[cur].changeColor();
            discard.deck.back().setColor(nextColor); // Change the color of the discard pile so next turn will have to match
            cout << endl << v[cur].getName() << " has changed the color to " << nextColor << endl;
            return next; // Doesn't skip a turn
        }
    }

    else if (c.getNumber() == 11) // If it is an action card
    {
        if (c.getName() == "Draw Two")
        {
            cout << endl << v[cur].getName() << " made " << v[next].getName() << " draw 2!" << endl;
            v[next].draw2(deck);

            print_hand(v[next]);               // Update player who drew 2 hand
            discard.deck.back().setNumber(12); // IF the number is not changed then the next person could play any action card since they are all the same numbers and drop() only checks if one vaiable is equal

            next += 1;            // Skip the next person's turn since they had to draw
            if (next >= v.size()) // To keep looping the order
                next = 0;

            return next;
        }

        else if (c.getName() == "Reverse")
        {
            cout << endl << v[cur].getName() << " has reversed the order!" << endl;

            discard.deck.back().setNumber(12); // IF the number is not changed then the next person could play any action card since they are all the same numbers and drop() only checks if one vaiable is equal
            next = reverse_order(v, v[cur].getName());
            return next;
        }

        else if (c.getName() == "Skip")
        {
            cout << endl << v[cur].getName() << " has skipped " << v[next].getName() << "!" << endl;

            discard.deck.back().setNumber(12); // IF the number is not changed then the next person could play any action card since they are all the same numbers and drop() only checks if one vaiable is equal
            next += 1;
            return next;
        }
    }

    else // no action needed
    {
        return next;
    }

    return next;
}

int reverse_order(vector<Player> &v, string name)
{
    // When a player reverses order, the person who played before them is now next.
    // So I return the index of the player who used the reverse card so I can just start from the next postion after reversing the order

    reverse(v.begin(), v.end()); // Reverse the order of playing

    int i;
    for (i = 0; i < v.size(); i++)
    {
        if (v[i].getName() == name)
            break;
    }

    i += 1; // go to next person's turn
    if (i >= v.size())
    {
        i = 0;
        return i;
    }
    else
    {
        return i;
    }

    return 0;
}

bool check_uno(const Player &p)
{
    if (p.hand.hand.size() == 1)
    {
        return true;
    }

    return false;
}

bool check_win(const Player &p)
{
    if (p.hand.hand.size() == 0)
    {
        cout << endl
             << endl
             << p.name << " wins!!!" << endl
             << endl;
        return true;
    }

    return false;
}
