#include "GameDisplay.hpp"
#include "Station.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "random"

using namespace mixr;

IMPLEMENT_SUBCLASS(GameDisplay, "GameDisplay")
EMPTY_SLOTTABLE(GameDisplay)
EMPTY_DELETEDATA(GameDisplay)

BEGIN_EVENT_HANDLER(GameDisplay)
	ON_EVENT_OBJ(3001, onSendCard, mixr::base::String)
END_EVENT_HANDLER()

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
			// sends the number of players to the controller
			getStation()->send("controller", 2001, playerCount, playerCountSD);

			// initialize game
			getStation()->send("controller", 2002);

			// switch to gameplayScreen
			newSubpage(gameplayScreen, nullptr);
		}
		break;

		// Draw card button (located on draw pile) 
		case 1009:
		{
			// call controller->DrawCard() function 
			getStation()->send("controller", 2003);
		}
		break;

		// below are the events for each of the buttons under the card for the player to use
			// however, we will likely need to do some thing else to account for which player's turn it is and how
			// that will operate
			// 
		// prev button
		case 1010:
		{
			std::cout << "Prev " << std::endl;
		}
		break;

		// next button
		case 1011:
		{
			std::cout << "Next " << std::endl;
		}
		break;

		// play button
		case 1012: 
		{
			std::cout << "Play " << std::endl;
		}
		break;
	}


}
void GameDisplay::updateData(const double dt)
{
	const auto page = static_cast<Pager*>(subpage());
	BaseClass::updateData(dt);
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

bool GameDisplay::onSendCard(mixr::base::String* textName)
{
	const auto pageStream = subPages();
	const auto textureList = getTextures();

	Pager* gameplayScreen = static_cast<Pager*>(pageStream->findByName("gameplayScreen")->object());

	Card* displayCard = dynamic_cast<Card*>(gameplayScreen->findByName("p1Top")->object());

	mixr::graphics::Polygon* testPoly = dynamic_cast<mixr::graphics::Polygon*>(displayCard->findByIndex(1)->object());

	mixr::base::Pair* testText = textureList->findByName(textName->getString());

	// this works! passing in a pair instead of object yieled the result we wanted
		// which was the index of the texture being returned
	const auto testNum = textureList->getIndex(testText);

	// why can we get the texture number here just fine but not over at gamecontroller?
	testPoly->setTexture(testNum);

	return true;
}