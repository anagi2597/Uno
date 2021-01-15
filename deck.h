#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <string>

class Player;

class Deck
{
private:
    std::vector<int> numbers = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9}; // All numbers needed
    std::vector<std::string> colors = {"Red", "Yellow", "Blue", "Green"};                 // All colors
    std::vector<std::string> action = {"Draw Two", "Reverse", "Skip"};                    // 2 of each color needed
    std::vector<std::string> wild = {"Draw Four", "Wild Card"};                           // 4 of each, no color needed

    Card c; // temp card object

public:

    std::vector<Card> deck;

    void create_deck();
    void shuffleDeck();
    virtual void get_description();
    friend bool can_drop(Player &p, Deck &discard);
};

#endif
