#pragma once

#include <string>

//Card class constructor
class Card
{
public:
    int value; //numerical value of card
    std::string suit; //spades, diamond, clubs, hearts
    std::string name; //name of card
    
    int getValue();
    std::string getSuit();
    std::string getName();
};