#include "Card.h" //include the header file so this file knows about the Card class and enums

//constructor definition
//initializes both the value and suit of a card when it is created
//uses an initialization list (the colon) to assign values directly instead of later in the body
Card::Card(Value v, Suit s) : value(v), suit(s) {
    //no code needed inside since both members are set above
}

//method definition that checks if two cards have the same suit
//"other" refers to another card being compared against this one
//the const at the end means this function cannot modify any class variables
bool Card::sameSuit(const Card& other) const {
    return suit == other.suit; //returns true if both cards share the same suit
}

//checks if two cards have the same value
//uses friend function so it can access private members of both cards
bool operator==(const Card& lhs, const Card& rhs) {
    return lhs.value == rhs.value; //returns true if both cards have identical value (e.g., both are Queens)
}

//checks if one cards value is less than another cards
bool operator<(const Card& lhs, const Card& rhs) {
    //static_cast converts the enum to an integer for comparison purposes
    return static_cast<int>(lhs.value) < static_cast<int>(rhs.value);
}

//checks if one cards value is greater than another card�s
bool operator>(const Card& lhs, const Card& rhs) {
    return static_cast<int>(lhs.value) > static_cast<int>(rhs.value);
}

//allows a card to be displayed using std::cout or other output streams
//example output: King of Hearts
std::ostream& operator<<(std::ostream& os, const Card& c) {
    //arrays that match each enum index to its corresponding text name
    static const std::string valueNames[] = {
        "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King", "Ace"
    };

    static const std::string suitNames[] = {
        "Clubs", "Diamonds", "Hearts", "Spades"
    };

    //formats and prints the card�s text form
    os << valueNames[static_cast<int>(c.value)]
        << " of "
        << suitNames[static_cast<int>(c.suit)];

    return os; //returns the stream to allow chaining (e.g., std::cout << c1 << c2)
}
