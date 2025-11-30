// Carlos Taylor
// CSC 339-01
// main.cpp
// Demonstrates the Card and Deck classes working together
// Creates several Card objects for comparison tests and uses a Deck object
// to simulate shuffling and drawing from a full 52-card deck.
// main.cpp  (driver exactly as specified)
#include "war.h"
#include <iostream>
#include <random>
#include <chrono>

int main() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto gen = std::default_random_engine{seed};

    auto war = War{gen};

    auto ws = WinState::ongoing;
    int countRounds = 0;
    while (ws == WinState::ongoing) {
        ws = war.playRound();
        ++countRounds;
    }
    std::cout << countRounds << " rounds total." << std::endl;

    return 0;
}
