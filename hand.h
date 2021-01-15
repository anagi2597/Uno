#ifndef HAND_H
#define HAND_H

#include "deck.h"
#include <string>
#include <vector>

class Hand : public Deck
{
private:
public:
    std::vector<Card> hand;

    void deal(Deck &d);
    void get_description();
    Hand operator+(Deck &d); // draw a card
    Card drop(int n); // drop a card
    int size();
};

#endif
