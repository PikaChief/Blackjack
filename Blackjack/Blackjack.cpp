
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Card class constructor
class Card
{
public:
    int value; //numerical value of card
    string suit; //spades, diamond, clubs, hearts
    string name; //name of card

    int getValue();
    string getSuit();
    string getName();
};

//returns card value
int Card::getValue()
{
    return value;
}

//returns card suit
string Card::getSuit()
{
    return suit;
}

//returns name of card
string Card::getName()
{
    return name;
}


//prints a vector of cards
void printDeck(vector<Card> deck)
{
    for (int i = 0; i < deck.size(); i++)
    {
        cout << deck[i].getName() + "\n";
    }
}

//shuffles deck (using swap)
void shuffle(vector<Card>& deck)
{
    srand(time(NULL));

    for(int i = 0; i < deck.size(); i++)
    {
        int random = rand() % (deck.size() - i) + i; //random position after i
        swap(deck[i], deck[random]); //swaps card at i with card at element random
    }
}

//shuffles deck (my version/unused) note: to call, you must set to temp vector 
vector<Card> MyShuffle(vector<Card> deck)
{
    srand(time(NULL)); //random seed
    vector<Card> temp;

    while (deck.size() > 0)
    {
        int random = rand() % deck.size(); //random position from deck
        temp.push_back(deck[random]); //inserts random card from deck into temp
        deck.erase(deck.begin() + random); //removes the same card from deck
    }
    return temp;
}

//draws a card from a vector
Card draw(vector<Card>& deck)
{
    int first_card_position = 0;
    Card card = deck.at(first_card_position);
    deck.erase(deck.begin() + first_card_position);
    
    return card;
}

int main()
{
    string values[13] = { "Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
    string suits[4] = { "Spades","Clubs","Diamonds","Hearts" };
    int worth[13] = { 1,2,3,4,5,6,7,8,9,10,10,10,10 };

    vector<Card> deck;
    
    for (int i = 0; i < 4; i++) //generates a deck of cards
    {
        for (int j = 0; j < 13; j++)
        {
            Card temp;
            temp.value = worth[j];
            temp.suit = suits[i];
            string card_name = values[j] + " of " + suits[i];
            temp.name = card_name;
            deck.push_back(temp);
        }
    }
    
    cout << "Deck in order: \n";
    printDeck(deck);

    cout << "\nThe shuffled deck is: \n";
    shuffle(deck);
    printDeck(deck);

    cout << "\nI drew two cards: \n";


    vector<Card> PlayerHand;

    Card floating_card = draw(deck);
    PlayerHand.push_back(floating_card);
    floating_card = draw(deck);
    PlayerHand.push_back(floating_card);

    printDeck(PlayerHand);


    cout << "\nThe shuffled deck should have the first two cards missing: \n";
    printDeck(deck);

    
}

