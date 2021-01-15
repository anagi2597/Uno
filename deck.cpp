#include "deck.h"
#include "card.h"
#include <iostream>
#include <vector>
#include <string>

// For shuffling function
#include <algorithm>
#include <random>
#include <chrono>

void Deck::create_deck()
{
    // Creating Numbered cards
    for (int i = 0; i < numbers.size(); i++)
    {
        for (int j = 0; j < colors.size(); j++)
        {
            c.setNumber(numbers[i]);
            c.setColor(colors[j]);
            c.setName(colors[j]);
            c.setFname();
            deck.push_back(c);
        }
    }

    // Creating action cards
    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < colors.size(); i++)
        {
            for (int j = 0; j < action.size(); j++)
            {
                c.setName(action[j]);
                c.setNumber(11);
                c.setColor(colors[i]);
                c.setFname();
                deck.push_back(c);
            }
        }
    }

    // Creating wild cards
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < wild.size(); j++)
        {
            c.setName(wild[j]);
            c.setNumber(10);
            c.setColor("none");
            c.setFname();
            deck.push_back(c);
        }
    }
};

void Deck::shuffleDeck()
{
    // new seed every time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // shuffle algorithm and random function
    shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
};

void Deck::get_description()
{
    std::cout << "Here is the top of the discard pile:" << std::endl;
    // for (int i = 0; i < deck.size(); i++)
    // {
    //     std::cout << i + 1 << ". " << deck[i].getFname() << std::endl;
    // }
    std::cout << deck.back().getFname() << std::endl;
};
