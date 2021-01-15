#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "uno.h"

#include <vector>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

// Static member
int Player::playerCount = 0;

int main()
{
    int num_plyrs = start_game(num_plyrs);

    Deck deck;      // Playable deck
    Deck discard;   // discard pile
    Card dropped_c; //  temp card
    deck.create_deck();
    deck.shuffleDeck();

    vector<Player> players;
    create_players(players, num_plyrs, deck);

    make_discard(deck, discard, dropped_c);

    // Main gameplay
    int i = 0;
    char c;
    bool win = false;
    bool uno = false;
    while(deck.deck.size() > 0)
    {
        cout << endl << endl;
        discard.get_description();
        cout << "It is " << players[i].getName() << "'s turn." << endl;

        if (can_drop(players[i], discard))
        {

            dropped_c = players[i].drop(discard); // Get the dropped card
            print_hand(players[i]);               // Update the player's hand

            uno = check_uno(players[i]); // Check if they have uno
            if (uno)
            {
                cout << endl << "Uno!" << endl;
                uno = false; // reset uno back to false
            }

            // If they win, end the game. No action needed
            win = check_win(players[i]);
            if (win)
                break;

            discard.deck.push_back(dropped_c); // Add dropped card to the discard pile
            i = check_card(players, i, deck, discard, dropped_c);

            if (i >= Player::playerCount) // To keep looping the order
                i = 0;
        }

        else
        {
            cout << "You do not have a valid card to drop. Please draw a card" << endl;
            Sleep(200); // Add a little time between turns
            players[i].draw(deck);
            print_hand(players[i]);

            i++; // next turn
            if (i >= Player::playerCount) // To keep looping the order
                i = 0;
        }
    }

    if(deck.deck.size() == 0)
        cout << "The deck is out of cards! No one won..." << endl;
    else if(win)
        cout << "Congratulations " << players[i].getName() << "! You Won!" << endl;

    cout << "Thanks for playing!" << endl << endl;

    return EXIT_SUCCESS;
}
