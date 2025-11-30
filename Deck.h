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
    explicit Deck(std::default_random_engine& gen) : nextIndex(0) {
        //create every suit/value pair
        for (int s = 0; s < 4; ++s) {
            for (int v = 0; v < 13; ++v) {
                cards.emplace_back(static_cast<Value>(v), static_cast<Suit>(s));
            }
        }
        //shuffle the deck so draws are random
        std::shuffle(cards.begin(), cards.end(), gen);
    }

    //draws the next card; returns nullptr when empty
    Card* draw() {
        if (nextIndex >= cards.size()) return nullptr;
        return &cards[nextIndex++];
    }

    //true when no more cards remain to draw
    bool empty() const { return nextIndex >= cards.size(); }
};

#endif
