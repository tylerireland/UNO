#ifndef __GameController_H__
#define __GameController_H__

#include "mixr/simulation/Simulation.hpp"
#include "Card.hpp"
#include <vector>
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
    void drawCard(int player);

    // shuffles the selected card pile
    std::vector<Card*> shuffleCards(std::vector<Card*> pile);

    // deals the cards to all the players in the game
    void dealCards();

    // will create all the necessary card piles required to start the game.
    void initializeGame();

private:

    int numPlayers{};
    int whoTurn{};

    std::vector<Card*> allCards{};
    std::vector<Card*> drawPile{};
    std::vector<Card*> discardPile{};
    std::vector<Card*> player1Pile{};
    std::vector<Card*> player2Pile{};
    std::vector<Card*> player3Pile{};
    std::vector<Card*> player4Pile{};
    std::vector<Card*> player5Pile{};
    std::vector<Card*> player6Pile{};
    std::vector<Card*> player7Pile{};
    std::vector<Card*> player8Pile{};
    std::vector<Card*> player9Pile{};
    std::vector<Card*> player10Pile{};


};

#endif