#ifndef __GameController_H__
#define __GameController_H__

#include "mixr/simulation/Simulation.hpp"
#include "Station.hpp"
#include "GameDisplay.hpp"
#include "Card.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/Component.hpp"
#include "random"


class GameController final : public mixr::simulation::Simulation
{
    DECLARE_SUBCLASS(GameController, mixr::simulation::Simulation)

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
    bool setPlayerCount(const mixr::base::Number* const num);

    int getTurn() { return whoTurn; }

    void nextPlayer(); 
    
    int randomNum();

    void showHand(mixr::base::PairStream* playerHand);

    bool event(const int event, mixr::base::Object* const obj = nullptr) override;

private:

    int numPlayers{};
    int whoTurn{1};
    int topOfDrawIdx{};
    int topOfDiscIdx{};

    bool cardsDealt = false;

    std::random_device seed;
    std::mt19937 gen{seed()}; // seed the generator
    std::uniform_int_distribution<> dist{1, 54}; // set min and max

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

    mixr::base::Pair* drawnCard{};
    SendData textureNameSD{};
    
};

#endif