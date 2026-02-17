#include "Deck.h"      //includes the Deck class definition
#include <algorithm>   //for std::shuffle

//builds a full 52-card deck and shuffles it using the provided generator
Deck::Deck(std::default_random_engine& gen)
    : nextIndex(0) {
    for (int s = 0; s < 4; ++s) {
        for (int v = 0; v < 13; ++v) {
            cards.emplace_back(static_cast<Value>(v), static_cast<Suit>(s));
        }
    }

    std::shuffle(cards.begin(), cards.end(), gen);
}

//draws the next card; returns nullptr when the deck is empty
Card* Deck::draw() {
    if (nextIndex >= cards.size()) return nullptr;
    return &cards[nextIndex++];
}

//true when no more cards remain to draw
bool Deck::empty() const {
    return nextIndex >= cards.size();
}
