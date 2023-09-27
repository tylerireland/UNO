#include "GameDisplay.hpp"

IMPLEMENT_SUBCLASS(GameDisplay, "GameDisplay")
EMPTY_SLOTTABLE(GameDisplay)
EMPTY_DELETEDATA(GameDisplay)

GameDisplay::GameDisplay()
{
	STANDARD_CONSTRUCTOR()
}

void GameDisplay::copyData(const GameDisplay& org, const bool)
{
	BaseClass::copyData(org);
}

void GameDisplay::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void GameDisplay::updateData(const double dt)
{
	BaseClass::updateData(dt);
}

void GameDisplay::reset()
{
	BaseClass::reset();
}