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
	ON_EVENT_OBJ(UPDATE_PLAYER_NUM, onUpdatePlayerNum, mixr::base::Number)
	ON_EVENT_OBJ(UPDATE_PLAYER_TURN, onUpdatePlayerTurnNum, mixr::base::Number)
	ON_EVENT_OBJ(UPDATE_TOTAL_CARD_COUNT, onUpdateTotalCards, mixr::base::Number)
	ON_EVENT_OBJ(UPDATE_CURRENT_CARD_NUM, onUpdateCurrentCard, mixr::base::Number)
END_EVENT_HANDLER()

GameDisplay::GameDisplay()
{
	STANDARD_CONSTRUCTOR()
}

void GameDisplay::copyData(const GameDisplay& org, const bool)
{
	BaseClass::copyData(org);
	currentCardSD.empty();
}

void GameDisplay::updateTC(const double dt)
{

	BaseClass::updateTC(dt);
}

void GameDisplay::buttonEvent(const int b)
{
	switch (b)
	{
		// setup menu button or "Play Game" button
		case PLAY_GAME_BUTTON:
		{
			newSubpage("setupScreen", nullptr);
		}
		break;

		// rules button
		case RULES_BUTTON:
		{
			newSubpage("rulesScreen", nullptr);
		}
		break;

		//back button to home screen (from rules screen)
		case BACK_BUTTON:
		{
			newSubpage("homeScreen", nullptr);
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
			newSubpage("homeScreen", nullptr);
		}
		break;

		// remove player buttun
		case REMOVE_PLAYER_BUTTON:
		{
			getStation()->send("controller", REMOVE_PLAYER);
		}
		break;

		// add player button
		case ADD_PLAYER_BUTTON:
		{
			getStation()->send("controller", ADD_PLAYER);
		}
		break;

		// start button
		case START_GAME_BUTTON:
		{
			// initialize game
			getStation()->send("controller", INIT_GAME);

			// switch to gameplayScreen
			newSubpage("gameplayScreen", nullptr);
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
			getStation()->send("controller", GET_CARD, -1, currentCardSD);
		}
		break;

		// next button
		case NEXT_CARD_BUTTON:
		{
			
			getStation()->send("controller", GET_CARD, 1, currentCardSD);
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
	currentCardSD.empty();
	playerTurnNumSD.empty();
	playerNumSD.empty();
	totalCardsSD.empty();
	currentCardNumSD.empty();
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

bool GameDisplay::onUpdatePlayerNum(mixr::base::Number* playerNumber)
{
	subpage()->send("playerCountNumber", UPDATE_VALUE, playerNumber, playerNumSD);
	
	return true;
}

bool GameDisplay::onUpdatePlayerTurnNum(mixr::base::Number* playerTurnNum)
{
	subpage()->send("playerTurnNumber", UPDATE_VALUE, playerTurnNum, playerTurnNumSD);

	return true;
}

bool GameDisplay::onUpdateTotalCards(mixr::base::Number* totalCards)
{
	subpage()->send("totalCards", UPDATE_VALUE, totalCards, totalCardsSD);
	return true;
}

bool GameDisplay::onUpdateCurrentCard(mixr::base::Number* currentCard)
{
	subpage()->send("cardNum", UPDATE_VALUE, currentCard, currentCardSD);
	return true;
}

