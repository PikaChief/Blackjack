
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

void printDeck(vector<Card> deck)
{
    for (int i = 0; i < deck.size(); i++)
    {
        cout << deck[i].getName() + "\n";
    }
}


//shuffles deck
void shuffle(vector<Card>& deck)
{
    srand(time(NULL));

    for(int i = 0; i < deck.size(); i++)
    {
        int random = rand() % (deck.size() - i) + i; //random position from deck
        swap(deck[i], deck[random]);
    }
}

//shuffles deck
vector<Card> MyShuffle(vector<Card> deck)
{
    srand(time(NULL));

    vector<Card> temp;

    while (deck.size() > 0)
    {
        int random = rand() % deck.size(); //random position from deck
        cout << random;
        temp.push_back(deck[random]); //inserts random card from deck into temp
        deck.erase(deck.begin() + random); //removes the same card from deck
    }
    return temp;
}

Card draw(vector<Card>& deck)
{
    int first_card_position = 0;
    Card card = deck.at(first_card_position);
    deck.erase(deck.begin() + first_card_position);
    
    return card;
}

int main()
{
    Card AceOfSpades;
    AceOfSpades.value = 1;
    AceOfSpades.suit = "Spades";
    AceOfSpades.name = "Ace of Spades";
    Card TwoOfSpades;
    TwoOfSpades.value = 2;
    TwoOfSpades.suit = "Spades";
    TwoOfSpades.name = "Two of Spades";
    Card ThreeOfSpades;
    ThreeOfSpades.value = 3;
    ThreeOfSpades.suit = "Spades";
    ThreeOfSpades.name = "Three of Spades";
    Card FourOfSpades;
    FourOfSpades.value = 4;
    FourOfSpades.suit = "Spades";
    FourOfSpades.name = "Four of Spades";
    Card FiveOfSpades;
    FiveOfSpades.value = 5;
    FiveOfSpades.suit = "Spades";
    FiveOfSpades.name = "Five of Spades";
    Card SixOfSpades;
    SixOfSpades.value = 6;
    SixOfSpades.suit = "Spades";
    SixOfSpades.name = "Six of Spades";
    Card SevenOfSpades;
    SevenOfSpades.value = 7;
    SevenOfSpades.suit = "Spades";
    SevenOfSpades.name = "Seven of Spades";
    Card EightOfSpades;
    EightOfSpades.value = 8;
    EightOfSpades.suit = "Spades";
    EightOfSpades.name = "Eight of Spades";
    Card NineOfSpades;
    NineOfSpades.value = 9;
    NineOfSpades.suit = "Spades";
    NineOfSpades.name = "Nine of Spades";
    Card TenOfSpades;
    TenOfSpades.value = 10;
    TenOfSpades.suit = "Spades";
    TenOfSpades.name = "Ten of Spades";
    Card JackOfSpades;
    JackOfSpades.value = 10;
    JackOfSpades.suit = "Spades";
    JackOfSpades.name = "Jack of Spades";
    Card QueenOfSpades;
    QueenOfSpades.value = 10;
    QueenOfSpades.suit = "Spades";
    QueenOfSpades.name = "Queen of Spades";
    Card KingOfSpades;
    KingOfSpades.value = 10;
    KingOfSpades.suit = "Spades";
    KingOfSpades.name = "Kings of Spades";
    Card AceOfClubs;
    AceOfClubs.value = 1;
    AceOfClubs.suit = "Clubs";
    AceOfClubs.name = "Ace of Clubs";
    Card TwoOfClubs;
    TwoOfClubs.value = 2;
    TwoOfClubs.suit = "Clubs";
    TwoOfClubs.name = "Two of Clubs";
    Card ThreeOfClubs;
    ThreeOfClubs.value = 3;
    ThreeOfClubs.suit = "Clubs";
    ThreeOfClubs.name = "Three of Clubs";
    Card FourOfClubs;
    FourOfClubs.value = 4;
    FourOfClubs.suit = "Clubs";
    FourOfClubs.name = "Four of Clubs";
    Card FiveOfClubs;
    FiveOfClubs.value = 5;
    FiveOfClubs.suit = "Clubs";
    FiveOfClubs.name = "Five of Clubs";
    Card SixOfClubs;
    SixOfClubs.value = 6;
    SixOfClubs.suit = "Clubs";
    SixOfClubs.name = "Six of Clubs";
    Card SevenOfClubs;
    SevenOfClubs.value = 7;
    SevenOfClubs.suit = "Clubs";
    SevenOfClubs.name = "Seven of Clubs";
    Card EightOfClubs;
    EightOfClubs.value = 8;
    EightOfClubs.suit = "Clubs";
    EightOfClubs.name = "Eight of Clubs";
    Card NineOfClubs;
    NineOfClubs.value =9;
    NineOfClubs.suit = "Clubs";
    NineOfClubs.name = "Nine of Clubs";
    Card TenOfClubs;
    TenOfClubs.value = 10;
    TenOfClubs.suit = "Clubs";
    TenOfClubs.name = "Ten of Clubs";
    Card JackOfClubs;
    JackOfClubs.value = 10;
    JackOfClubs.suit = "Clubs";
    JackOfClubs.name = "Jack of Clubs";
    Card QueenOfClubs;
    QueenOfClubs.value = 10;
    QueenOfClubs.suit = "Clubs";
    QueenOfClubs.name = "Queen of Clubs";
    Card KingOfClubs;
    KingOfClubs.value = 10;
    KingOfClubs.suit = "Clubs";
    KingOfClubs.name = "King of Clubs";

    /*
    for (int card = 1, card < 52, card++)
    {
        for (int suit = 1, suit < 13, suit++)
        {
            "Two " +
            vector with names of suits/numbers, then set position equal to the name
        }
    }
    */

    vector<Card> deck;

    deck.push_back(AceOfSpades);
    deck.push_back(TwoOfSpades);
    deck.push_back(ThreeOfSpades);
    deck.push_back(FourOfSpades);
    deck.push_back(FiveOfSpades);

    cout << "Deck in order: \n";
    printDeck(deck);

   
    cout << "The shuffled deck is: \n";

    shuffle(deck);
    printDeck(deck);

    cout << "I drew a card: \n";

    Card card = draw(deck);
    cout << card.getName() + "\n";

    cout << "The shuffled deck should have first card missing: \n";
    printDeck(deck);


    
    penis;

    /*vector<Card> newDeck;
    newDeck = shuffle(deck);

    printDeck(newDeck);*/
    
    
}

