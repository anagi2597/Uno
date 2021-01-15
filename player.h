#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include <string>
#include <vector>

class Player
{
private:
    std::string name;
    std::string filename;
    

public:
    Player(std::string name, Deck &d);
    ~Player();
    
    static int playerCount;
    Hand hand;

    std::string getName();
    void setName(std::string name);

    std::string getFilename();
    void setFilename();

    friend void print_hand(const Player &p);
    friend bool can_drop(Player &p, Deck &discard);
    friend bool check_uno(const Player &p);
    friend bool check_win(const Player &p);

    void draw(Deck &d);
    void draw2(Deck &d);
    void draw4(Deck &d);
    Card drop(Deck &d);
    std::string changeColor();
};

#endif