#include "Deck.h"     //includes the Deck class definition
#include <algorithm>  //for std::shuffle
#include <iostream>   //for console output when testing

//constructor definition
//sets up the 52 cards and automatically shuffles them into the draw pile
Deck::Deck(std::default_random_engine& _gen)
    : gen(_gen) //initializes the reference to the random number generator
{
    //defines the 4 suits in a constant array for easy looping
    constexpr auto suitVec = std::array<Suit, 4>{
        Suit::Clubs, Suit::Diamonds, Suit::Hearts, Suit::Spades
    };

    //defines the 13 possible card values in a constant array
    constexpr auto valueVec = std::array<Value, 13>{
        Value::Two, Value::Three, Value::Four, Value::Five, Value::Six, Value::Seven,
        Value::Eight, Value::Nine, Value::Ten, Value::Jack, Value::Queen, Value::King, Value::Ace
    };

    //creates every combination of suit and value (4 suits × 13 values = 52 cards)
    for (auto s : suitVec) {
        for (auto v : valueVec) {
            //creates a new Card object on the heap using a unique pointer
            cards.push_back(std::make_unique<Card>(v, s));
        }
    }

    //automatically shuffle the deck once it's been filled
    reshuffle();
}

//reshuffles the entire deck and refills the draw pile with all 52 cards
void Deck::reshuffle() {
    //randomly reorders the cards in the vector using the provided generator
    std::shuffle(cards.begin(), cards.end(), gen);

    //creates a temporary stack to hold the shuffled cards
    std::stack<Card*> tmpStack;

    //loops through each unique_ptr<Card> in the vector
    for (auto& card : cards) {
        //pushes the raw pointer version of the unique_ptr onto the stack
        tmpStack.push(card.get());
    }

    //swaps the contents of tmpStack with the actual drawPile
    drawPile.swap(tmpStack);
}

//draws the top card from the deck and returns it
//returns nullptr if no cards remain in the pile
Card* Deck::draw() {
    //checks if the stack is empty
    if (drawPile.empty()) {
        return nullptr; //no cards left to draw
    }

    //gets the top card pointer, removes it from the stack, and returns it
    Card* topCard = drawPile.top();
    drawPile.pop();
    return topCard;
}
