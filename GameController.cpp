#include "GameController.hpp"

IMPLEMENT_SUBCLASS(GameController, "GameController")

EMPTY_SLOTTABLE(GameController)
EMPTY_DELETEDATA()

GameController::GameController()
{
	STANDARD_CONSTRUCTOR()
}

void GameController::copyData(const GameController& org, const bool)
{
	BaseClass::copyData(org);
}

void GameController::deleteData()
{

}

