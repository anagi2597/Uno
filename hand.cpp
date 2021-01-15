#include "hand.h"
#include <iostream>
#include <vector>
#include <fstream>

void Hand::deal(Deck &d)
{
    int i;
    for(i = 0; i < 7; i++)
    {
        hand.push_back(d.deck.at(i));
    }

    d.deck.erase(d.deck.begin(), d.deck.begin() + i); // removing the 7 cards from the deck
};

void Hand::get_description()
{
    std::cout << "Here is your current hand:" << std::endl;
    for (int i = 0; i < hand.size(); i++)
    {
        std::cout << i + 1 << ". " << hand[i].getFname() << std::endl;
    }
};

Hand Hand::operator+(Deck &d)
{
    hand.push_back(d.deck[0]); // draw the top card
    d.deck.erase(d.deck.begin(), d.deck.begin() + 1);

    return *this;
}

Card Hand::drop(int n)
{
    Card c;
    c = hand.at(n);
    hand.erase(hand.begin() + n);

    return c;
}

int Hand::size()
{
    return hand.size();
}
