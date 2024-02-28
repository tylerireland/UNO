#include "GameDisplay.hpp"
#include "Station.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "random"
#include "MyMacros.cpp"

IMPLEMENT_SUBCLASS(GameDisplay, "GameDisplay")
EMPTY_SLOTTABLE(GameDisplay)
EMPTY_DELETEDATA(GameDisplay)

BEGIN_EVENT_HANDLER(GameDisplay)
	ON_EVENT_OBJ(SET_TEXTURE, onSendCard, mixr::base::String)
	ON_EVENT_OBJ(NEXT_PLAYER, onNextPlayer, mixr::base::Number)
END_EVENT_HANDLER()

GameDisplay::GameDisplay()
{
	STANDARD_CONSTRUCTOR()
	playerCountSD.empty();
	playerTurnSD.empty();
}

void GameDisplay::copyData(const GameDisplay& org, const bool)
{
	BaseClass::copyData(org);

	playerCount = org.playerCount;
	playerCountSD.empty();
	currentCardSD.empty();
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
		case PLAY_GAME_BUTTON:
		{
			newSubpage(setupScreen, nullptr);
		}
		break;

		// rules button
		case RULES_BUTTON:
		{
			newSubpage(rulesScreen, nullptr);
		}
		break;

		//back button to home screen (from rules screen)
		case BACK_BUTTON:
		{
			newSubpage(homeScreen, nullptr);
		}
		break;

		// quit button on home screen
		case QUIT_BUTTON:
		{
			exit(EXIT_SUCCESS);
		}
		break;

		// menu button (from setup screen)
		case MENU_BUTTON:
		{
			newSubpage(homeScreen, nullptr);
		}
		break;

		// remove player buttun
		case REMOVE_PLAYER_BUTTON:
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
		case ADD_PLAYER_BUTTON:
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
		case START_GAME_BUTTON:
		{
			// sends the number of players to the controller
			getStation()->send("controller", SET_PLAYER_COUNT, playerCount, playerCountSD);

			// initialize game
			getStation()->send("controller", INIT_GAME);

			// switch to gameplayScreen
			newSubpage(gameplayScreen, nullptr);
		}
		break;

		// Draw card button (located on draw pile) 
		case DRAW_CARD_BUTTON:
		{
			// call controller->DrawCard() function 
			getStation()->send("controller", DRAW_CARD);
		}
		break;

		// below are the events for each of the buttons under the card for the player to use
			// however, we will likely need to do some thing else to account for which player's turn it is and how
			// that will operate
			// 
		// prev button

		case PREVIOUS_CARD_BUTTON:
		{
			std::cout << "Prev " << std::endl;
		}
		break;

		// next button
		case NEXT_CARD_BUTTON:
		{
			std::cout << "Next " << std::endl;
			currentCard++;
		}
		break;

		// play button
		case PLAY_CARD_BUTTON: 
		{
			getStation()->send("controller", SHOW_HAND);
		}
		break;
	}


}
void GameDisplay::updateData(const double dt)
{
	std::cout << subpageName() << std::endl;
	BaseClass::updateData(dt);
}

mixr::simulation::Simulation* GameDisplay::getSimulation()
{
	mixr::simulation::Simulation* s{};
	mixr::simulation::Station* sta{getStation()};
	if (sta != nullptr) s = sta->getSimulation();
	return s;
}

mixr::simulation::Station* GameDisplay::getStation()
{
	if (stn == nullptr) {
		const auto s = dynamic_cast<mixr::simulation::Station*>(findContainerByType(typeid(mixr::simulation::Station)));
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

bool GameDisplay::onNextPlayer(mixr::base::Number* playerNum)
{
	playerTurn = playerNum->getInt();
	return true;
}