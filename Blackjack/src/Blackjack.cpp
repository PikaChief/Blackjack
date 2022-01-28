
#include <iostream>
#include <string>
#include <vector>

#include "Card.h"

using namespace std;


//Player Class
class Player
{
public:
    string name;
    int bankroll;
    int bet;
    vector<Card> hand;

    string getName();
    int getBankroll();
    int getBet();
    vector<Card> getHand();

};

string Player::getName()
{
    return name;
}
int Player::getBankroll()
{
    return bankroll;
}
int Player::getBet()
{
    return bet;
}
vector<Card> Player::getHand()
{
    return hand;
}



vector<Card> generateDeck()
{
    string values[13] = { "Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King" };
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
    return deck;
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
    for(int i = 0; i < deck.size(); i++)
    {
        int random = rand() % (deck.size() - i) + i; //random position after i
        swap(deck[i], deck[random]); //swaps card at i with card at element random
    }
}

//alternative shuffle method. Note: to call, you must set to a temp vector 
vector<Card> MyShuffle(vector<Card> deck)
{
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

int sum(vector<Card> hand)
{
    int sum = 0;
    for (int i = 0; i < hand.size(); i++)
    {
        sum += hand[i].getValue();
    }
    return sum;
}

int main()
{
    srand(time(NULL));
    vector<Card> deck;
    
    Player dealer;
    dealer.name = "Dealer";

    Player player1;
    bool play = true;

     
    cout << "Hello, welcome to Blackjack! Please type your name: ";
    string input_name;
    cin >> input_name;
    player1.name = input_name;

     
    while (play == true)
    {
        deck = generateDeck();
        shuffle(deck);

        //player bet
        /*
        cout << "Input your bet: ";
        int input_bet;
        cin >> input_bet;
        player1.bet = input_bet;
        player1.bankroll -= bet;
        */

        //play begins
        dealer.hand.push_back(draw(deck));
        dealer.hand.push_back(draw(deck));

        cout << "\nThe dealer's face-up card is: \n";
        cout << dealer.hand[1].getName();

        player1.hand.push_back(draw(deck));
        player1.hand.push_back(draw(deck));

        cout << "\n\nThe player's hand is: \n";
        printDeck(player1.getHand());
        cout << "Your total is: " + to_string(sum(player1.getHand()));

        //player action
        cout << "\nWould you like to (H)it or (S)tand? ";
        string action;
        cin >> action;
        while (action == "H")
        {
            player1.hand.push_back(draw(deck));
            cout << "\nYour hand is: \n";
            printDeck(player1.getHand());
            cout << "Your total is: " + to_string(sum(player1.getHand()));

            if (sum(player1.getHand()) > 21)
            {
                cout << "\nYou busted!\n";
                action = "S";
            }
            else
            {
                cout << "\nWould you like to (H)it or (S)tand? ";
                cin >> action;
            }
        }
        //only if player did not bust
        if (sum(player1.getHand()) < 22) 
        {
            cout << "\nThe dealer's hand was: \n";
            printDeck(dealer.getHand());

            while (sum(dealer.getHand()) < 17)
            {
                dealer.hand.push_back(draw(deck));
                cout << "\nThe dealer hit: \n";
                printDeck(dealer.getHand());
                cout << "The dealer's total is: " + to_string(sum(dealer.getHand())) + "\n";
            }
            if (sum(dealer.getHand()) > 21)
            {
                cout << "The dealer busted. You win!\n";
                //player1.bankroll += bet;
                //player1.bankroll += bet;
            }
            else
            {
                if (sum(dealer.getHand()) > sum(player1.getHand()))
                {
                    cout << "The Dealer won.";
                }
                if (sum(dealer.getHand()) < sum(player1.getHand()))
                {
                    cout << "Congratulations, you win!";
                    //player1.bankroll += bet;
                    //player1.bankroll += bet;
                }
                if (sum(dealer.getHand()) == sum(player1.getHand()))
                {
                    cout << "It's a Push. Bets are returned.";
                    //player1.bankroll += bet;
                }
            }
        }

        //resetting deck and hands
        dealer.hand.clear();
        player1.hand.clear();
        deck.clear();

        //continuation
        cout << "\nWould you like to play again? Y/N: ";
        string answer;
        cin >> answer;
        if (answer == "N")
        {
            play = false;
        }
        cout << "============================================================";
    }
    
        
}

