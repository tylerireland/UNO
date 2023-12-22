#include "GameController.hpp"
#include "Pager.hpp"
#include <GL/glut.h>

#include "mixr/graphics/Page.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/Component.hpp"

#include "random"

using namespace mixr;

IMPLEMENT_SUBCLASS(GameController, "GameController")

EMPTY_SLOTTABLE(GameController)
EMPTY_DELETEDATA(GameController)

GameController::GameController()
{
	STANDARD_CONSTRUCTOR()
}

bool GameController::cardIsPlayable(Card* card)
{
	// if statement here to check the front of the discardPile vector and compare it to the card being given to the function
		// change this to top of discard instead of draw pile
	if (dynamic_cast<Card*>(findByIndex(topOfDeckIdx)->object())->getCardType() == card->getCardType() || dynamic_cast<Card*>(findByIndex(topOfDeckIdx)->object())->getCardColor() == card->getCardColor())
	{
		return true;
	}

	return false;
}

void GameController::initializeGame()
{

	// access station
	stn = static_cast<Station*>(findContainerByType(typeid(Station)));

	// null pointer check to make sure station is there
	if (stn != nullptr)
	{
		std::cout << "Number of players: ";

		std::cout << numPlayers << std::endl;

		std::cout << std::endl;

		topOfDeckIdx = randomNum(); // generate number
			
		dealCards();

		std::cout << "Player 1 hand: ";

		std::cout << std::endl;

		showHand(player1Pile);

		std::cout << "Player 2 hand: ";

		std::cout << std::endl;

		showHand(player2Pile);

		std::cout << std::endl;

		std::cout << "Player 3 hand: ";

		std::cout << std::endl;

		showHand(player3Pile);

		std::cout << std::endl;

		std::cout << "Player 4 hand: ";

		std::cout << std::endl;

		showHand(player4Pile);

		std::cout << std::endl;

		std::cout << "Player 5 hand: ";

		std::cout << std::endl;

		showHand(player5Pile);

		std::cout << std::endl;

		std::cout << "Player 6 hand: ";

		std::cout << std::endl;

		showHand(player6Pile);

		std::cout << std::endl;

		std::cout << "Player 7 hand: ";

		std::cout << std::endl;

		showHand(player7Pile);

		std::cout << std::endl;

		std::cout << "Player 8 hand: ";

		std::cout << std::endl;

		showHand(player8Pile);

		std::cout << std::endl;

		std::cout << "Player 9 hand: ";

		std::cout << std::endl;

		showHand(player9Pile);

		std::cout << std::endl;

		std::cout << "Player 10 hand: ";

		std::cout << std::endl;

		showHand(player10Pile);

		whoTurn = 1;


	}
}

void GameController::drawCard()
{
	base::Pair* testCard = (findByIndex(topOfDeckIdx));

	switch (whoTurn)
	{
	case 1:

		player1Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 2:

		player2Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 3:
		player3Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 4:
		player4Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 5:
		player5Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 6:
		player6Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 7:
		player7Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 8:
		player8Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 9:
		player9Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	case 10:
		player10Pile->put(testCard);

		topOfDeckIdx = randomNum();

		nextPlayer();

		break;
	default:
		break;
	}
}


// obsolete now? 
mixr::base::PairStream* GameController::shuffleCards(mixr::base::PairStream* pile)
{
	int size = pile->entries();
	
	// this no longer works because it was designed for vectors. need to redo this

	// algorithm to swap that may or may not work
		// iter_swap is supposed swap two elements when give two interators
	//for (int i = 0; i < size - 1; i++) // we iterate through the size of the pile
	{
		//int j = i + rand() % (size - i); // j is the current iterator i PLUS a random nunber modulus the pile size, which gives us a random element
		//iter_swap(pile->getFirstItem()->getValue() + i, pile->getFirstItem()->getValue() + j); // then the element at i is swapped with the element at j 
	}
	// i found this through the algorithm library, so we'll see if this even works. 
	// there might be a much easier way to shuffle the cards, but this seemed fun to explore 



	// not sure if this would work but holy crap am I tired right now
	return pile;
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
}

void GameController::setPlayerCount(int num)
{
	numPlayers = num;
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



