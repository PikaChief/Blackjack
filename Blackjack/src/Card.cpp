#include "Card.h"

//returns card value
int Card::getValue()
{
    return value;
}
//returns card suit
std::string Card::getSuit()
{
    return suit;
}
//returns name of card
std::string Card::getName()
{
    return name;
}