#include "GameDisplay.hpp"
#include "Station.hpp"


using namespace mixr;

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
	playerCountSD.empty();
}

void GameDisplay::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void GameDisplay::buttonEvent(const int b)
{
	// PairStream of all pages 
	const auto pageStream = subPages();

	// define and put each page in variable
	Pager* homeScreen = static_cast<Pager*>(pageStream->findByName("homeScreen")->object());
	Pager* rulesScreen = static_cast<Pager*>(pageStream->findByName("rulesScreen")->object());
	Pager* setupScreen = static_cast<Pager*>(pageStream->findByName("setupScreen")->object());
	Pager* gameplayScreen = static_cast<Pager*>(pageStream->findByName("gameplayScreen")->object());
	
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

		// start button
		case 1008:
		{

			// grab simulation (GameController)
			GameController* sim = dynamic_cast<GameController*>(getSimulation());
			
			// set the player count after it has been confirmed by user
			sim->setPlayerCount(playerCount);

			// initialize everything
			sim->initializeGame();

			// switch to gameplayScreen
			newSubpage(gameplayScreen, nullptr);


		}
		break;

		// Draw card button (located on draw pile) 
		case 1009:
		{
	
			GameController* sim = dynamic_cast<GameController*>(getSimulation());

			sim->drawCard();

			//sim->showHand();
		}
		break;
	}


}
void GameDisplay::updateData(const double dt)
{
	// can't remember why this is here, maybe it just needs to be
	const auto page = static_cast<Pager*>(subpage());
	
	BaseClass::updateData(dt);

	// this is not displaying on the setupPage for whatever reason
		// "playerCount" is in the setupPage.epp and all seems well. Not sure why it's not appearing
	send("playerCount", UPDATE_VALUE, playerCount, playerCountSD);
}

simulation::Simulation* GameDisplay::getSimulation()
{
	simulation::Simulation* s{};
	simulation::Station* sta{getStation()};
	if (sta != nullptr) s = sta->getSimulation();
	return s;
}

simulation::Station* GameDisplay::getStation()
{
	if (stn == nullptr) {
		const auto s = dynamic_cast<simulation::Station*>(findContainerByType(typeid(simulation::Station)));
		if (s != nullptr) stn = s;
	}
	return stn;
}

void GameDisplay::reset()
{
	BaseClass::reset();
}