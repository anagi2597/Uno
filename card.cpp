#include "card.h"

std::string Card::getName()
{
    return this->name;
}
void Card::setName(std::string name)
{
    this->name = name;
}

std::string Card::getColor()
{
    return this->color;
}
void Card::setColor(std::string color)
{
    this->color = color;
}

int Card::getNumber()
{
    return this->number;
}
void Card::setNumber(int number)
{
    this->number = number;
}

std::string Card::getFname()
{
    return this->fname;
}
void Card::setFname()
{
    if (number == 10) // Wild cards
        fname = name;

    else if (number == 11) // action cards
    {
        fname = color + " " + name;
    }
    else // Regular cards
        fname = name + " " + std::to_string(number);
}
