#ifndef CARD_H //if not defined yet
#define CARD_H //define Card.h so it only loads once per compile

//we will need features from these libraries
#include <iostream> // for input/output 
#include <string>   //for using text objects to represent names (for suits/values)

//uses safe enumaration variables which are tied to underlying integer values
//allows them to be ordered and used for comparison later
enum class Suit { Clubs, Diamonds, Hearts, Spades };
enum class Value { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

//defines the Card class that stores a suit and value for each card
class Card {
private:
    const Suit suit;   //the suit of the card (Clubs, Diamonds, Hearts, Spades)
    const Value value; //the value of the card (Two through Ace)

public:
    //constructor assigns both the value and suit when the card is created
    Card(Value v, Suit s);

    //compares this card�s suit to another card�s suit and returns true if they match
    bool sameSuit(const Card& other) const;

    //friend functions allow direct access to private members for comparing and displaying cards
    friend bool operator==(const Card& lhs, const Card& rhs); //returns true if both cards have the same value
    friend bool operator<(const Card& lhs, const Card& rhs);  //returns true if left card value is lower than right card value
    friend bool operator>(const Card& lhs, const Card& rhs);  //returns true if left card value is higher than right card value

    //output operator for printing the card as text (example: �Queen of Hearts�)
    friend std::ostream& operator<<(std::ostream& os, const Card& c);
};

#endif //ends the Card.h include guard so it doesn�t load multiple times
