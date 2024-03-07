
#include "GameController.hpp"
#include "Pager.hpp"
#include <GL/glut.h>

#include "mixr/graphics/Page.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/Component.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "MyMacros.cpp"

#include "random"

using namespace mixr;

IMPLEMENT_SUBCLASS(GameController, "GameController")

EMPTY_SLOTTABLE(GameController)
EMPTY_DELETEDATA(GameController)

BEGIN_EVENT_HANDLER(GameController)
	ON_EVENT_OBJ(SET_PLAYER_COUNT, setPlayerCount, mixr::base::Number)
	ON_EVENT(INIT_GAME, initializeGame)
	ON_EVENT(DRAW_CARD, drawCard)
	ON_EVENT(SHOW_HAND, showHand)
	ON_EVENT(ADD_PLAYER, addPlayer)
	ON_EVENT(REMOVE_PLAYER, removePlayer)
	ON_EVENT_OBJ(GET_CARD, getPlayersCard, mixr::base::Number)
	
END_EVENT_HANDLER()

GameController::GameController()
{
	STANDARD_CONSTRUCTOR()
	textureNameSD.empty();
	playerTurnSD.empty();
	cardCountSD.empty();
	currentCardSD.empty();
	//playerList = new mixr::base::PairStream();
}

bool GameController::cardIsPlayable(Card* card)
{
	// if statement here to check the front of the discardPile vector and compare it to the card being given to the function
		// change this to top of discard instead of draw pile
	if (dynamic_cast<Card*>(findByIndex(topOfDiscIdx)->object())->getCardType() == card->getCardType() || 
		dynamic_cast<Card*>(findByIndex(topOfDiscIdx)->object())->getCardColor() == card->getCardColor())
	{
		return true;
	}

	return false;
}

bool GameController::initializeGame()
{
	for (int i = 1; i < numPlayers + 1; i++)
	{
		Player* newPlayer = new Player(i, 10, 10);

		// sets player 1's turn
		if (i == 1) newPlayer->setTurn(true);


		// temp bc pair cast returns null
		//mixr::base::Pair* playerPair = dynamic_cast<mixr::base::Pair*>(newPlayer);
		//playerList->put(playerPair);


		playerList.push_back(newPlayer);
	}

	topOfDrawIdx = randomNum(); // generate number
		
	dealCards();

	return true;
}

bool GameController::drawCard()
{
	topOfDrawIdx = randomNum(); // generate number
	drawnCard = (findByIndex(topOfDrawIdx));


	if (getPlayer()->getPlayerNum() == 1)
	{
		// get a random card from the deck 
		Card* currentCard = dynamic_cast<Card*>(drawnCard->object());

		// create a string of the texture name by getting the currentCard's color and type
		mixr::base::String* textureName = new mixr::base::String(currentCard->getCardColor().c_str(), currentCard->getCardType().c_str());

		// send that texture string over to the display so it can change the top of the hand to the drawn card
		getStation()->send("display", SET_TEXTURE, textureName, textureNameSD);

		// unref here, yes?
		textureName->unref();
	}
	

	// add card to the player's hand
	getPlayer()->addCard(drawnCard);
	// move to the next player
	nextPlayer();

	return true;
}

void GameController::dealCards()
{
	for (int i = 0; i < 7; i++)  // deals seven cards
	{
		for (int j = 0; j < numPlayers; j++)
		{
			drawCard();  // using drawCard to give the card to player j
		}
	}

	cardsDealt = true;
}

bool GameController::setPlayerCount(const mixr::base::Number* const num)
{
	numPlayers = num->getInt();

	return true;
}

void GameController::nextPlayer()
{
	/*
	for (int i = 1; i < numPlayers + 1, i++;)
	{
		
		Player* player = dynamic_cast<Player*>(playerList->getPosition(i));
		if (player->isMyTurn())
		{
			player->setTurn(false);

			if (i + 1 > numPlayers + 1)
				player = dynamic_cast<Player*>(playerList->getPosition(1));
			else
				player = dynamic_cast<Player*>(playerList->getPosition(i+1));
			
			player->setTurn(true);

			return;
		}
	}
	*/

	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList.at(i)->isMyTurn())
		{
			playerList.at(i)->setTurn(false);

			if (i + 1 <= playerList.size() - 1)
				playerList.at(i+1)->setTurn(true);
			else
				playerList.at(0)->setTurn(true);

			return;
		}
	}
}

int GameController::randomNum()
{
	return dist(gen);
}

bool GameController::showHand()
{
	std::cout << "Player " << getPlayer(0)->getPlayerNum() << "'s Hand: " << std::endl;
	getPlayer(0)->showHand();
	return true;
}

void GameController::copyData(const GameController& org, const bool)
{
	BaseClass::copyData(org);
}

void GameController::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void GameController::updateData(const double dt)
{
	if (getPlayer())
	{
		playerTurnSD.empty();
		cardCountSD.empty();
		currentCardSD.empty();
		getStation()->send("display", UPDATE_PLAYER_TURN, getPlayer()->getPlayerNum(), playerTurnSD);
		getStation()->send("display", UPDATE_TOTAL_CARD_COUNT, getPlayer()->getTotalCards(), cardCountSD);
		getStation()->send("display", UPDATE_CURRENT_CARD_NUM, getPlayer()->getCurrentCardIndex(), currentCardSD);
	}

	getStation()->send("display", UPDATE_PLAYER_NUM, numPlayers, numPlayersSD);
	BaseClass::updateData(dt);
}

Player* GameController::getPlayer()
{
	for (Player* player : playerList)
	{
		if (player->isMyTurn())
		{
			return player;
		}
	}
	
	/*
	for (int i = 1; i < numPlayers + 1, i++;)
	{
		Player* player = dynamic_cast<Player*>(playerList->getPosition(i));
		if (player->isMyTurn())
		{
			return player;
		}
	}
	*/
}

Player* GameController::getPlayer(int index)
{
	return playerList.at(index);
}

bool GameController::addPlayer()
{
	if (numPlayers < 10)
	{
		numPlayers++;
		return true;
	}
	return false;
}

bool GameController::removePlayer()
{
	if (numPlayers > 2)
	{
		numPlayers--;
		return true;
		// send the setupscreen the number of players
	}
	return false;
}

bool GameController::getPlayersCard(mixr::base::Number* nextOrPrev)
{
	Card* currentCard = getPlayer()->getCard(nextOrPrev->getInt());
	// create a string of the texture name by getting the currentCard's color and type
	mixr::base::String* textureName = new mixr::base::String(currentCard->getCardColor().c_str(), currentCard->getCardType().c_str());
	// send that texture string over to the display so it can change the top of the hand to the drawn card
	getStation()->send("display", SET_TEXTURE, textureName, textureNameSD);

	return true;
}

