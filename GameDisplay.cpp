#include "GameDisplay.hpp"

IMPLEMENT_SUBCLASS(GameDisplay, "GameDisplay")
EMPTY_SLOTTABLE(GameDisplay)
EMPTY_DELETEDATA(GameDisplay)

GameDisplay::GameDisplay()
{
	STANDARD_CONSTRUCTOR()

	playerCountSD.empty();

}

void GameDisplay::copyData(const GameDisplay& org, const bool)
{
	BaseClass::copyData(org);

	playerCount = org.playerCount;
}

void GameDisplay::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void GameDisplay::buttonEvent(const int b)
{
	const auto pageStream = subPages();

	Pager* homeScreen = static_cast<Pager*>(pageStream->findByName("homeScreen")->object());
	Pager* rulesScreen = static_cast<Pager*>(pageStream->findByName("rulesScreen")->object());
	Pager* setupScreen = static_cast<Pager*>(pageStream->findByName("setupScreen")->object());
	Pager* gameplayScreen = static_cast<Pager*>(pageStream->findByName("gameplayScreen")->object());
	GameController* controller = static_cast<GameController*>(findByName("gameController")->object());

	switch (b)
	{
		// setup menu button or "Play Game" button
		case 1001:
		{
			newSubpage(setupScreen, nullptr);
		}
		break;

		// rules button
		case 1002:
		{
			newSubpage(rulesScreen, nullptr);
		}
		break;

		//back button to home screen
		case 1003:
		{
			newSubpage(homeScreen, nullptr);
		}
		break;

		// quit button on home screen
		case 1004:
		{
			exit(EXIT_SUCCESS);
		}
		break;

		case 1005:
		{
			newSubpage(homeScreen, nullptr);
		}
		break;

		// remove player buttun
		case 1006:
		{
			if (playerCount == 2)
			{
				std::cout << "Cannot have less than two players!" << std::endl;
				break;
			}
			else
			{
				playerCount = playerCount - 1;
			}
		}
		break;

		// add player button
		case 1007:
		{
			if (playerCount == 10)
			{
				std::cout << "Cannot exceed 10 players!" << std::endl;
				break;
			}
			else
			{
				playerCount = playerCount + 1;
			}
		}
		break;

		case 1008:
		{
			// also add in an assignment of the chosen playerCount 
			controller->initializeGame(playerCount);
			newSubpage(gameplayScreen, nullptr);
		}
		break;
	}


}
void GameDisplay::updateData(const double dt)
{

	const auto page = static_cast<Pager*>(subpage());
	
	BaseClass::updateData(dt);
}

void GameDisplay::reset()
{
	BaseClass::reset();
}