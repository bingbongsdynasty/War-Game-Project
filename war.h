// war.h
#ifndef WAR_H
#define WAR_H

//we will need features from these libraries
#include <queue>      //for player hands
#include <vector>     //for the middle pile
#include <utility>    //for std::pair
#include <random>     //for shuffling middle
#include <algorithm>  //for std::shuffle
#include <iostream>   //for printing messages
#include "Card.h"     //for Card, Suit, Value, and printing
#include "deck.h"     //for Deck

//game outcome for a round or final state
enum class WinState { winA, winB, tie, ongoing };

//keeps track of what kind of sub-round comes next
enum class PlayState { normal, warDown, warUp };

//simulates the card game War
class War {
private:
    std::default_random_engine& gen;  //random source shared from main
    Deck deck;                        //the shuffled deck for this game

    //each player's hand; front is the top card, back is the bottom
    std::queue<Card*> handA;
    std::queue<Card*> handB;

    //cards in the middle of the table waiting for the winner
    std::vector<Card*> middle;

    //tracks where we are inside a round
    PlayState state;

    //helper that places one face-up or face-down card from each player
    std::pair<Card*, Card*> placeCards(bool faceUp);

    //helper that shuffles the middle and gives it to the chosen player
    void collectRound(std::queue<Card*>& to);

    //checks if someone is out of cards after a collection
    WinState checkForWin();

    //updates state machine and prints messages after a sub-round
    void updateState(bool cardsMatch);

    //runs one sub-round (one pair of placements, up or down)
    WinState subRound();

public:
    //constructor deals the full deck: 26 to each player, alternating
    explicit War(std::default_random_engine& _gen);

    //plays one full round; returns ongoing or a final result
    WinState playRound();
};

#endif
