#ifndef __GameController_H__
#define __GameController_H__

#include "mixr/base/Component.hpp"
#include "Card.hpp"

//------------------------------------------------------------------------------
// Class: Controller
//
// Description: Puzzle controller
//------------------------------------------------------------------------------
class GameController final : public mixr::base::Component
{
    DECLARE_SUBCLASS(GameController, mixr::base::Component)

public:

    GameController();

    bool isCardPlayable(Card* card);
    void playerDraw();
    
    
private:

    int playerCount{};
    int currTurn{};

    

};

#endif