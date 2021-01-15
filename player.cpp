#include "player.h"
#include "hand.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

Player::Player(std::string name, Deck &d)
{
    this->name = name;
    filename = name + ".txt";
    hand.deal(d);
    Player::playerCount += 1;
}

Player::~Player()
{
}

std::string Player::getName()
{
    return this->name;
}
void Player::setName(std::string name)
{
    this->name = name;
}

std::string Player::getFilename()
{
    return this->filename;
}
void Player::setFilename()
{
    this->filename = name + ".txt";
}

void Player::draw(Deck &d)
{
    hand.operator+(d);
}

void Player::draw2(Deck &d)
{
    for (int i = 0; i < 2; i++)
        hand.operator+(d);
}

void Player::draw4(Deck &d)
{
    for (int i = 0; i < 4; i++)
        hand.operator+(d);
}

Card Player::drop(Deck &discard)
{
    int drop;
    bool go = true;

    // Checking if card selection is valid
    while (go == true)
    {
        std::cout << "Which card would you like to drop?" << std::endl;
        std::cin >> drop;
        std::cin.ignore(1000, '\n');
        drop -= 1;

        if (drop < 0 || drop >= hand.size()) // Check range
        {
            std::cout << "Not within the range." << std::endl;
            continue;
        }
        // Check if either same color, number, or if it's a wild card
        else if (hand.hand[drop].getName() == discard.deck.back().getName() || hand.hand[drop].getNumber() == discard.deck.back().getNumber() || hand.hand[drop].getNumber() == 10 || hand.hand[drop].getColor() == discard.deck.back().getColor())
        {
            go = false;
        }
        else
        {
            std::cout << "You can't drop that card! Pick another." << std::endl;
            continue;
        }
    }

    Card c;
    c = hand.drop(drop);
    return c;
}

std::string Player::changeColor()
{
    std::string color = "";
    while (color != "Red" && color != "Blue" && color != "Yellow" && color != "Green")
    {
        std::cout << "What color would you like to change to? (Red, Blue, Yellow, or Green): ";
        std::cin >> color;
        std::cin.ignore(1000, '\n');

        color[0] = toupper(color[0]);
        for (int i = 1; i < color.length(); i++)
        {
            color[i] = tolower(color[i]);
        }

        // color = "";
        // std::cout << "Not a valid color" << std::endl;
        // std::cout << "What color would you like to change to?: ";
        // std::cin >> color;
        // std::cin.ignore(1000, '\n');
    }

    return color;
}
