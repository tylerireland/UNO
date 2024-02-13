
#include "GameController.hpp"
#include "Pager.hpp"
#include <GL/glut.h>

#include "mixr/graphics/Page.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/Component.hpp"
#include "mixr/graphics/Polygon.hpp"

#include "random"

using namespace mixr;

IMPLEMENT_SUBCLASS(GameController, "GameController")

EMPTY_SLOTTABLE(GameController)
EMPTY_DELETEDATA(GameController)

BEGIN_EVENT_HANDLER(GameController)
	ON_EVENT_OBJ(2001, setPlayerCount, mixr::base::Number)
	ON_EVENT(2002, initializeGame)
	ON_EVENT(2003, drawCard)
	
END_EVENT_HANDLER()

GameController::GameController()
{
	STANDARD_CONSTRUCTOR()
	textureNameSD.empty();
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
		switch(i)
		{
		case 1: 
			player1Pile = new mixr::base::PairStream();
			break;
		case 2: 
			player2Pile = new mixr::base::PairStream();
			break;
		case 3:
			player3Pile = new mixr::base::PairStream();
			break;
		case 4:
			player4Pile = new mixr::base::PairStream();
			break;
		case 5:
			player5Pile = new mixr::base::PairStream();
			break;
		case 6:
			player6Pile = new mixr::base::PairStream();
			break;
		case 7:
			player7Pile = new mixr::base::PairStream();
			break;
		case 8: 
			player8Pile = new mixr::base::PairStream();
			break;
		case 9:
			player9Pile = new mixr::base::PairStream();
			break;
		case 10: 
			player10Pile = new mixr::base::PairStream();
			break;
		default:
			break;
		}

	}

	std::cout << "Number of players: ";

	std::cout << numPlayers << std::endl;

	std::cout << std::endl;

	topOfDrawIdx = randomNum(); // generate number
		
	dealCards();

	std::cout << "Player 1 hand: ";

	std::cout << std::endl;

	showHand(player1Pile);

	std::cout << "Player 2 hand: ";

	std::cout << std::endl;

	showHand(player2Pile);

	std::cout << std::endl;

	whoTurn = 1;

	return true;
}

bool GameController::drawCard()
{
	drawnCard = (findByIndex(topOfDrawIdx));

 	if (cardsDealt == true)
	{
		// get card from pair 
		Card* currentCard = dynamic_cast<Card*>(drawnCard->object());

		// create a string of the texture name by getting the currentCard's color and type
		mixr::base::String* textureName = new mixr::base::String(currentCard->getCardColor().c_str(), currentCard->getCardType().c_str());

		// send that texture string over to the display so it can change the top of the hand to the drawn card
		getStation()->send("display", 3001, textureName, textureNameSD);

		// unref here, yes?
		textureName->unref();

	}

	switch (whoTurn)
	{
	case 1:

		player1Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		return true;
		break;
	case 2:

		player2Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		return true;
		break;
	case 3:
		player3Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	case 4:
		player4Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	case 5:
		player5Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	case 6:
		player6Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	case 7:
		player7Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	case 8:
		player8Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	case 9:
		player9Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	case 10:
		player10Pile->put(drawnCard);

		topOfDrawIdx = randomNum();

		nextPlayer();

		break;
	default:
		break;
	}

	return true;
}

void GameController::dealCards()
{
	//  dealCards should only be called inside of initializeCardDecks()!!! We may rename that function to initializeGame().
	// this function assumes the drawPile has been shuffled.
	

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
	if (whoTurn + 1 > numPlayers)
	{
		whoTurn = 1;
	}
	else
	{
		whoTurn++;
	}

}

int GameController::randomNum()
{
	return dist(gen);
}

void GameController::showHand(base::PairStream* playerHand)
{

	std::cout << std::endl;

	for (size_t i = 1; i < playerHand->entries() + 1; i++)
	{
		std::cout << "Card type: ";

		std::cout << dynamic_cast<Card*>(playerHand->getPosition(i)->object())->getCardType() << std::endl;

		std::cout << "Card color: ";

		std::cout << dynamic_cast<Card*>(playerHand->getPosition(i)->object())->getCardColor() << std::endl;

		std::cout << std::endl;
	}

	//std::cout << "Number of cards: " << player1Pile->entries() << std::endl;

	//std::cout << "Test: " << player1Pile->getPosition(0);

	//std::cout << "Index = 1: " << dynamic_cast<Card*>(player1Pile->getPosition(1)->object())->getCardType() << std::endl;

	//std::cout << "Index = 5: " << dynamic_cast<Card*>(player1Pile->getPosition(5)->object())->getCardType() << std::endl;

	//std::cout << "Index = 7: " << dynamic_cast<Card*>(player1Pile->getPosition(7)->object())->getCardType() << std::endl;

}

void GameController::copyData(const GameController& org, const bool)
{
	BaseClass::copyData(org);
}



