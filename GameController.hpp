#ifndef __GameController_H__
#define __GameController_H__

#include "mixr/simulation/Simulation.hpp"
#include "Station.hpp"
#include "GameDisplay.hpp"
#include "Card.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/Component.hpp"
#include "Player.hpp"
#include "random"

using namespace mixr;
using namespace base;
using namespace simulation;

class GameController final : public Simulation
{
    DECLARE_SUBCLASS(GameController, Simulation)

public:

    GameController();

    // returns true if the selected card can play on the discard pile
    bool cardIsPlayable(Card* card);

    // moves a card from the drawPile to the selected player's pile
    bool drawCard();

    // deals the cards to all the players in the game
    void dealCards();

    // will create all the necessary card piles required to start the game.
    bool initializeGame();

    // display can use this function to give us the player count
        // BUT what if we just tried to use a send function instead?
    bool setPlayerCount(const Number* const num);

    void nextPlayer(); 
    
    int randomNum();

    void showHand(PairStream* playerHand);

    bool event(const int event, Object* const obj = nullptr) override;

private:

    int numPlayers{};
    int topOfDrawIdx{};
    int topOfDiscIdx{};

    bool cardsDealt = false;

    // list of all the players in game
    PairStream* playerList{};


    Pair* drawnCard{};
    SendData textureNameSD{};

    // variables for random number generator
    std::random_device seed;
    std::mt19937 gen{seed()}; // seed the generator
    std::uniform_int_distribution<> dist{1, 54}; // set min and max
};

#endif