#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
private:
    std::string name;  // Name ex reverse, draw 2
    std::string color; // Color of card
    int number;
    std::string fname; // full name. ex: green 6

public:
    std::string getName();
    void setName(std::string name);

    std::string getColor();
    void setColor(std::string color);

    int getNumber();
    void setNumber(int number);

    std::string getFname();
    void setFname();
};

#endif
