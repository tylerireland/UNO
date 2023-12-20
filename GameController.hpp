#ifndef __GameController_H__
#define __GameController_H__

#include "mixr/simulation/Simulation.hpp"
#include "Station.hpp"
#include "GameDisplay.hpp"
#include "Card.hpp"
#include "mixr/base/PairStream.hpp"
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
    

private:

    int numPlayers{};
    int whoTurn{1};
    int topOfDeck{};

    mixr::base::PairStream* allCards{};
    mixr::base::PairStream* drawPile{};
    mixr::base::PairStream* discardPile{};
    mixr::base::PairStream* player1Pile{};
    mixr::base::PairStream* player2Pile{};
    mixr::base::PairStream* player3Pile{};
    mixr::base::PairStream* player4Pile{};
    mixr::base::PairStream* player5Pile{};
    mixr::base::PairStream* player6Pile{};
    mixr::base::PairStream* player7Pile{};
    mixr::base::PairStream* player8Pile{};
    mixr::base::PairStream* player9Pile{};
    mixr::base::PairStream* player10Pile{};

    Station* stn{};
};

#endif