
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
    vector<Card> hand2; //for splits
    vector<Card> softhand; //for soft hands
    vector<Card> softhand2; //for soft split hands

    string getName();
    int getBankroll();
    int getBet();
    vector<Card> getHand();
    vector<Card> getHand2();
    vector<Card> getSoftHand();
    vector<Card> getSoftHand2();
    void clearHands();
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
vector<Card> Player::getHand2()
{
    return hand2;
}
vector<Card> Player::getSoftHand()
{
    return softhand;
}
vector<Card> Player::getSoftHand2()
{
    return softhand2;
}
void Player::clearHands()
{
    hand.clear();
    hand2.clear();
    softhand.clear();
    softhand2.clear();
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
    for (int i = 0; i < deck.size(); i++)
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

//returns sum of a vector of cards
int sum(vector<Card> hand)
{
    int sum = 0;
    for (int i = 0; i < hand.size(); i++)
    {
        sum += hand[i].getValue();
    }
    return sum;
}

//returns true if a vector of cards contains an Ace
bool hasAce(vector<Card> hand)
{
    bool ace = false;
    for (int i = 0; i < hand.size(); i++)
    {
        if (hand[i].getValue() == 1)
        {
            ace = true;
        }
    }
    return ace;
}

//checks Player1's hand for Ace to make soft hand
void updateSoftHand(vector<Card> original, vector<Card>& softhand)
{
    softhand.clear(); //softhand needs to be cleared so previous function calls don't accumulate

    //copies original's hand into soft hand
    for (int i = 0; i < original.size(); i++)
    {
        softhand.push_back(original[i]);
    }

    //sets first Ace in the soft hand to 11
    for (int i = 0; i < softhand.size(); i++)
    {
        if (((softhand[i].getValue() == 1)))
        {
            softhand[i].value = 11;
            i = softhand.size(); //breakout of loop because only first Ace value in a hand gets set to 11
        }
    }
}

int main()
{

    srand(time(NULL));
    vector<Card> deck;

    Player dealer;
    dealer.name = "Dealer";

    Player player1;
    player1.name = "Player 1";

    bool game = true;;

    /*
    cout << "Hello, welcome to Blackjack! Please type your name: ";
    string input_name;
    cin >> input_name;
    player1.name = input_name;
    */


    while (game == true)
    {
        string turn = "Setup"; //Setup, Player1, Dealer, none (results)

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
        //dealer.hand.push_back(deck[0]);
        //dealer.hand.push_back(deck[13]);

        cout << "\nThe dealer's face-up card is: \n";
        //cout << dealer.hand[0].getName();
        cout << dealer.hand[1].getName();

        player1.hand.push_back(draw(deck));
        player1.hand.push_back(draw(deck));
        //player1.hand.push_back(deck[46]);
        //player1.hand.push_back(deck[48]);

        cout << "\n\nThe player's hand is: \n";
        printDeck(player1.getHand());


        //checks Dealer's hand for Ace to make soft hand
        if (hasAce(dealer.getHand()))
        {
            updateSoftHand(dealer.hand, dealer.softhand);
        }

        //checks Player1's hand for Ace to make soft hand
        if (hasAce(player1.getHand()))
        {
            updateSoftHand(player1.hand, player1.softhand);
        }

        //PLAYER BLACKJACK
        if ((sum(player1.getSoftHand()) == 21) && !(sum(dealer.getSoftHand()) == 21))
        {
            cout << "Winner Winner Chicken Dinner!";
            turn = "none"; //game is over, acutally might not be if you want player blackjack + dealer blakcjack = push
        }

        //DEALER BLACKJACK
        else if ((dealer.hand[0].value == 1) && (dealer.hand[1].value == 10)) //Dealer Blackjack = first (face-down) card is Ace and second (face-up card) is 10
        {
            if (sum(player1.getSoftHand()) == 21)
            {
                cout << "Player and Dealer both has Blackjack. It's a Push.";
            }
            else cout << "Dealer has Blackjack!";
            turn = "none"; //game is over
        }

        //INSURANCE
        else if (dealer.hand[1].value == 1) //only if Dealer 2nd (face-up) card is Ace
        {
            cout << "Would you like insurance? Y/N: ";
            string response;
            cin >> response;
            if (response == "Y")
            {
                cout << "You took insurance."; //unfinished
                //player1.bankroll -= bet/2;
            }
            if (response == "N")
            {
                cout << "You declined insurance.";
            }

            if ((dealer.hand[1].value == 1) && (dealer.hand[0].value == 10))
            {
                cout << "\nSorry. the Dealer had Blackjack.";
                turn = "none"; //game is over
            }
        }

        while (turn == "Setup")
        {
            //soft hand text
            if (hasAce(player1.getHand()))
            {
                //displays soft hand total, if applicable
                cout << "\nYour total is: " + to_string(sum(player1.getHand())) + " or " + to_string(sum(player1.getSoftHand()));
            }
            else
            {
                //normal text 
                cout << "\nYour total is: " + to_string(sum(player1.getHand()));
            }
            turn = "Player 1";
        }

        //PLAYER 1'S TURN
        while (turn == "Player 1")
        {
            //Player action/hit loop
            cout << "\nWould you like to (H)it, (S)tand, or (D)ouble Down? ";
            string action;
            cin >> action;


            //if (action == "D") //doubles the bet if double down
            //{
            //    player1.bet += player1.bet; 
            //}

            while ((action == "H") || (action == "D"))
            {
                //draws one card
                Card temp;
                temp = draw(deck);
                player1.hand.push_back(temp);

                //prints hand
                cout << "\nYour hand is: \n";
                printDeck(player1.getHand());

                //updates soft_hand to include the new card, if at least one Ace in hand
                if ((hasAce(player1.getHand())))
                {
                    updateSoftHand(player1.hand, player1.softhand);
                    if (sum(player1.getSoftHand()) <= 21)//won't print out if soft total is over 21
                    {
                        cout << "Your total is: " + to_string(sum(player1.getHand())) + " or " + to_string(sum(player1.getSoftHand()));
                    }
                    else
                    {
                        cout << "Your total is: " + to_string(sum(player1.getHand()));
                    }
                }
                else
                {
                    cout << "Your total is: " + to_string(sum(player1.getHand()));
                }

                //post action cases
                if (sum(player1.getHand()) > 21)
                {
                    cout << "\nYou busted!\n";
                    action = "S";
                    turn = "Dealer"; //or next player's turn, array/vector?
                }
                else if (action == "D")
                {
                    action = "S"; //if player chose to double down, they are not allowed to hit again
                    cout << "\n";
                }
                else
                {
                    cout << "\nWould you like to (H)it or (S)tand? ";
                    cin >> action;
                }
            }

            //clears and fills player1's hand with soft hand values if it is higher
            if (((sum(player1.getSoftHand())) <= 21) && ((sum(player1.getHand()))) < sum((player1.getSoftHand())))
            {
                player1.hand.clear();
                for (int i = 0; i < player1.softhand.size(); i++)
                {
                    player1.hand.push_back(player1.softhand[i]);
                }
            }
            turn = "Dealer"; //or next player
        }

        //DEALER'S TURN
        while (turn == "Dealer") //or next player
        {
            //dealer normal text
            cout << "\nThe dealer's hand was: \n";
            printDeck(dealer.getHand());

            cout << "The Dealer's total was: " + to_string(sum(dealer.getHand()));
            //dealer soft hand text
            if (hasAce(dealer.getHand())) //always displays if Dealer first two cards had Ace because total will never be over 21
            {
                updateSoftHand(dealer.hand, dealer.softhand);
                if (sum(dealer.getSoftHand()) <= 21) //won't print out if soft total is over 21
                {
                    cout << " or " + to_string(sum(dealer.getSoftHand()));
                }

                //replaces dealer's hard hand with soft hand, if soft hand is between 17-21
                if ((17 <= (sum(dealer.getSoftHand())) <= 21) && ((sum(dealer.getHand())) < sum(dealer.getSoftHand())))
                {
                    dealer.hand.clear();
                    for (int i = 0; i < dealer.softhand.size(); i++)
                    {
                        dealer.hand.push_back(dealer.softhand[i]);
                    }
                }
            }

            //Dealer action/hit loop
            while (((sum(dealer.getHand()) < 17) && sum(dealer.getSoftHand()) < 17)) //Dealer stands on hard 17 and soft 17s
            {
                //draws one card
                Card temp;
                temp = draw(deck);
                dealer.hand.push_back(temp);

                cout << "\nThe dealer hit: \n";
                printDeck(dealer.getHand());

                //dealer soft hand text
                if (hasAce(dealer.getHand()))
                {
                    //also puts drawn card in soft hand, if applicable
                    updateSoftHand(dealer.hand, dealer.softhand);

                    if (sum(dealer.getSoftHand()) <= 21) //displays soft hand total, if soft hand is under 22
                    {
                        cout << "The dealer's total is: " + to_string(sum(dealer.getHand())) + " or " + to_string(sum(dealer.getSoftHand()));

                        //replaces dealer's hand with soft hand values, but only if the soft hand isn't busted
                        if ((17 <= (sum(dealer.getSoftHand())) <= 21) && ((sum(dealer.getHand())) < sum(dealer.getSoftHand())))
                        {
                            dealer.hand.clear();
                            for (int i = 0; i < dealer.softhand.size(); i++)
                            {
                                dealer.hand.push_back(dealer.softhand[i]);
                            }
                        }
                    }
                    else
                    {
                        //clears dealer's softhand if it busts, as it will be updated next loop when dealer hits again
                        if (sum(dealer.getSoftHand()) > 21)
                        {
                            dealer.softhand.clear();
                        }
                    }
                }
                else
                {
                    cout << "The dealer's total is: " + to_string(sum(dealer.getHand()));
                }


            }

            turn = "Calculation"; //Dealer is last player to go
        }

        while (turn == "Calculation")
        {

            cout << "\n\nThe dealer's final score is: " + to_string((sum(dealer.getHand())));
            cout << "\nPlayer 1's final score is: " + to_string((sum(player1.getHand())));

            //END OF GAME CALCULATIONS
            if ((sum(dealer.getHand())) > 21 && (sum(player1.getHand()) < 22))
            {
                cout << "\nThe dealer busted. You win!\n";
                //player1.bankroll += bet;
                //player1.bankroll += bet;
            }
            else
            {
                if ((sum(dealer.getHand()) > sum(player1.getHand())) && (sum(player1.getHand()) < 22))
                {
                    cout << "\nThe Dealer won.";
                }
                else if ((sum(dealer.getHand()) < sum(player1.getHand())) && (sum(player1.getHand()) < 22))
                {
                    cout << "\nCongratulations, you win!";
                    //player1.bankroll += bet;
                    //player1.bankroll += bet;
                }
                else if (sum(dealer.getHand()) == sum(player1.getHand()))
                {
                    cout << "\nIt's a Push. Bets are returned.";
                    //player1.bankroll += bet;
                }
            }
            turn = "none";
        }

        //resetting deck and hands MAKER A FUNCTION FOR THIS
        dealer.clearHands();
        player1.clearHands();
        deck.clear();

        //continuation
        cout << "\nWould you like to play again? Y/N: ";
        string answer;
        cin >> answer;
        if (answer == "Y")
        {
            turn = "Setup"; //resets turn back to Setup
        }
        if (answer == "N")
        {
            game = false;
        }
        cout << "============================================================";
    }


}

