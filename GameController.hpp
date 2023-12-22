#ifndef __GameController_H__
#define __GameController_H__

#include "mixr/simulation/Simulation.hpp"
#include "Station.hpp"
#include "GameDisplay.hpp"
#include "Card.hpp"
#include "mixr/base/PairStream.hpp"

#include "random"
//------------------------------------------------------------------------------
// Class: Controller
//
// Description: Puzzle controller
//------------------------------------------------------------------------------
class GameController final : public mixr::simulation::Simulation
{
    DECLARE_SUBCLASS(GameController, mixr::simulation::Simulation)

public:

    GameController();

    // returns true if the selected card can play on the discard pile
    bool cardIsPlayable(Card* card);

    // moves a card from the drawPile to the selected player's pile
    void drawCard();

    // shuffles the selected card pile
    mixr::base::PairStream* shuffleCards(mixr::base::PairStream* pile);

    // deals the cards to all the players in the game
    void dealCards();

    // will create all the necessary card piles required to start the game.
    void initializeGame();

    // display can use this function to give us the player count
        // BUT what if we just tried to use a send function instead?
    void setPlayerCount(int num);

    int getTurn() { return whoTurn; }

    void nextPlayer(); 
    
    int randomNum();

    void showHand(mixr::base::PairStream* playerHand);

private:

    int numPlayers{};
    int whoTurn{1};
    int topOfDeckIdx{};

    std::random_device seed;
    std::mt19937 gen{seed()}; // seed the generator
    std::uniform_int_distribution<> dist{1, 54}; // set min and max

    mixr::base::PairStream* allCards{};
    mixr::base::PairStream* drawPile{};
    mixr::base::PairStream discardPile[1]{};
    mixr::base::PairStream player1Pile[1]{};
    mixr::base::PairStream player2Pile[1]{};
    mixr::base::PairStream player3Pile[1]{};
    mixr::base::PairStream player4Pile[1]{};
    mixr::base::PairStream player5Pile[1]{};
    mixr::base::PairStream player6Pile[1]{};
    mixr::base::PairStream player7Pile[1]{};
    mixr::base::PairStream player8Pile[1]{};
    mixr::base::PairStream player9Pile[1]{};
    mixr::base::PairStream player10Pile[1]{};

    Station* stn{};
};

#endif