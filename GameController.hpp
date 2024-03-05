#ifndef __GameController_H__
#define __GameController_H__

#include "mixr/simulation/Simulation.hpp"
#include "Station.hpp"
#include "GameDisplay.hpp"
#include "Card.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/Component.hpp"
#include "mixr/base/Pair.hpp"
#include "Player.hpp"
#include "random"
#include <vector>

class GameController final : public mixr::simulation::Simulation
{
    DECLARE_SUBCLASS(GameController, Simulation)

public:

    GameController();

    void updateTC(const double dt = 0.0) final;
    void updateData(const double dt = 0.0) final;

    // returns true if the selected card can play on the discard pile
    bool cardIsPlayable(Card* card);

    // moves a card from the drawPile to the selected player's pile
    bool drawCard();

    // deals the cards to all the players in the game
    void dealCards();

    // will create all the necessary card piles required to start the game.
    bool initializeGame();

    // sets the player count from display
    bool setPlayerCount(const mixr::base::Number* const num);
    
    // generate a random number
    int randomNum();

    // show current players hand
    bool showHand();

    bool event(const int event, Object* const obj = nullptr) override;

    // returns the player whose turn it is
    Player* getPlayer();
    Player* getPlayer(int index);

    // move to the next player
    void nextPlayer();

    bool addPlayer();
    bool removePlayer();

private:

    int numPlayers{2};
    SendData numPlayersSD;

    int topOfDrawIdx{};
    int topOfDiscIdx{};

    bool cardsDealt = false;

    // list of all the players in game
    //mixr::base::PairStream* playerList{};

    // temp vector to store player objects
    std::vector<Player*> playerList{};

    mixr::base::Pair* drawnCard{};
    SendData textureNameSD{};
    SendData playerTurnSD{};

    // variables for random number generator
    std::random_device seed;
    std::mt19937 gen{seed()}; // seed the generator
    std::uniform_int_distribution<> dist{1, 54}; // set min and max
};

#endif