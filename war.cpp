// war.cpp
#include "war.h"

//constructor: initialize members, then deal alternating until deck is empty
War::War(std::default_random_engine& _gen)
    : gen(_gen), deck(_gen), state(PlayState::normal) {

    //alternate dealing to simulate real life
    auto* current = &handA;
    auto* other   = &handB;

    while (Card* c = deck.draw()) {
        current->push(c);
        std::swap(current, other);
    }
}

//places one card from each player into the middle
//faceUp controls printing: true prints the two cards; false prints face-down message
std::pair<Card*, Card*> War::placeCards(bool faceUp) {
    Card* cardA = nullptr;
    Card* cardB = nullptr;

    if (!handA.empty()) { cardA = handA.front(); handA.pop(); middle.push_back(cardA); }
    if (!handB.empty()) { cardB = handB.front(); handB.pop(); middle.push_back(cardB); }

    if (faceUp) {
        if (cardA && cardB) {
            std::cout << "Player A plays " << *cardA
                      << " | Player B plays " << *cardB << std::endl;
        } else {
            if (cardA) {
                std::cout << "Player A plays " << *cardA << std::endl;
            } else {
                std::cout << "Player A cannot play a card." << std::endl;
            }

            if (cardB) {
                std::cout << "Player B plays " << *cardB << std::endl;
            } else {
                std::cout << "Player B cannot play a card." << std::endl;
            }
        }
    } else {
        std::cout << "Players playing one card each, face down..." << std::endl;
    }

    return {cardA, cardB};
}

//gives the shuffled middle pile to the specified hand
void War::collectRound(std::queue<Card*>& to) {
    std::shuffle(middle.begin(), middle.end(), gen);
    while (!middle.empty()) {
        Card* c = middle.back();
        middle.pop_back();
        to.push(c);
    }
}

//checks if any player is out of cards after a collection
WinState War::checkForWin() {
    bool aEmpty = handA.empty();
    bool bEmpty = handB.empty();

    if (aEmpty && bEmpty) {
        std::cout << "Both players are out of cards at the same time. It is a tie." << std::endl;
        return WinState::tie;
    }
    if (aEmpty) {
        std::cout << "Player A is out of cards; player B wins." << std::endl;
        return WinState::winB;
    }
    if (bEmpty) {
        std::cout << "Player B is out of cards; player A wins." << std::endl;
        return WinState::winA;
    }
    return WinState::ongoing;
}

//updates the state machine and reports war status
void War::updateState(bool cardsMatch) {
    if (state == PlayState::normal) {
        if (cardsMatch) {
            std::cout << "Cards have same value. War!" << std::endl;
            state = PlayState::warDown; //next step is one face-down each
        } else {
            state = PlayState::normal;  //round ended normally
        }
        return;
    }

    if (state == PlayState::warDown) {
        //after placing face-down, next is face-up comparison
        state = PlayState::warUp;
        return;
    }

    if (state == PlayState::warUp) {
        if (cardsMatch) {
            std::cout << "Cards have same value. War continues." << std::endl;
            state = PlayState::warDown; //repeat the sequence
        } else {
            state = PlayState::normal;  //war resolved
        }
    }
}

//one sub-round according to current state
WinState War::subRound() {
    bool needFaceUp = (state == PlayState::normal) || (state == PlayState::warUp);
    auto [cardA, cardB] = placeCards(needFaceUp);

    //if either player could not place a card when required, end the game
    if (needFaceUp) {
        if (!cardA && !cardB) {
            std::cout << "Both players are out of cards at the same time. It is a tie." << std::endl;
            return WinState::tie;
        }
        if (!cardA) {
            std::cout << "Player A is out of cards; player B wins." << std::endl;
            return WinState::winB;
        }
        if (!cardB) {
            std::cout << "Player B is out of cards; player A wins." << std::endl;
            return WinState::winA;
        }
    } else {
        if (!cardA && !cardB) {
            std::cout << "Both players are out of cards at the same time. It is a tie." << std::endl;
            return WinState::tie;
        }
        if (!cardA) {
            std::cout << "Player A is out of cards; player B wins." << std::endl;
            return WinState::winB;
        }
        if (!cardB) {
            std::cout << "Player B is out of cards; player A wins." << std::endl;
            return WinState::winA;
        }

        //face-down step; advance the state machine and continue
        updateState(false);
        return WinState::ongoing;
    }

    //compare face-up cards
    bool cardsMatch = (*cardA == *cardB);
    if (!cardsMatch) {
        if (*cardA > *cardB) {
            std::cout << "Player A has the higher card and wins the "
                      << (state == PlayState::normal ? "round." : "war.") << std::endl;
            collectRound(handA);
        } else {
            std::cout << "Player B has the higher card and wins the "
                      << (state == PlayState::normal ? "round." : "war.") << std::endl;
            collectRound(handB);
        }
    }

    //show hand sizes after any collection
    auto pluralize = [](size_t n) { return n == 1 ? " card" : " cards"; };
    std::cout << "(Player A has " << handA.size() << pluralize(handA.size())
              << "; player B has " << handB.size() << pluralize(handB.size())
              << ".)" << std::endl;

    //check for an ending
    auto ws = checkForWin();
    if (ws != WinState::ongoing) return ws;

    //update war/normal state for the next sub-round or next round
    updateState(cardsMatch);
    return WinState::ongoing;
}

//plays one full round; keeps looping only while a war is resolving
WinState War::playRound() {
    WinState ws = WinState::ongoing;
    //always start a new external round in whatever state we are already in
    do {
        ws = subRound();
    } while (ws == WinState::ongoing && state != PlayState::normal);
    return ws;
}
