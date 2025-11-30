// deck.h
#ifndef DECK_H
#define DECK_H

//we will need these standard libraries
#include <vector>    //for storing the 52 cards
#include <random>    //for shuffling with a provided generator
#include "Card.h"    //for Suit and Value and Card

//represents a standard 52-card deck that can be shuffled and drawn from
class Deck {
private:
    std::vector<Card> cards;  //the actual card objects; deck owns the storage
    std::size_t nextIndex;    //index of the next card to draw

public:
    //builds a full deck and shuffles it using the provided generator
    explicit Deck(std::default_random_engine& gen);

    //draws the next card; returns nullptr when empty
    Card* draw();

    //true when no more cards remain to draw
    bool empty() const;
};

#endif
