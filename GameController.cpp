#include "GameController.hpp"
#include "Pager.hpp"
#include <GL/glut.h>

#include "mixr/graphics/Page.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/Component.hpp"

#include "random"

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
	if (dynamic_cast<Card*>(findByIndex(topOfDeck)->object())->getCardType() == card->getCardType() || dynamic_cast<Card*>(findByIndex(topOfDeck)->object())->getCardColor() == card->getCardColor())
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

		// get all cards (54) created in game controller into a pairStream
		//allCards = getComponents();
	
		// check that 54 are there
		//std::cout << "Number of total cards: ";
		//std::cout << allCards->entries() << std::endl;

		// to check converion from pairStream to Card object, grab first card pair out of pair stream
			// should be red zero 
		//mixr::base::Pair* cardPair = findByIndex(1);

		// convert Pair to Card
			// we cast the object we pull from the Pair with "->object()"
			// that seems to be the way we extract objects from Pairs
		//Card* testCard = dynamic_cast<Card*>(cardPair->object());

		// tests 
		//std::cout << testCard->getCardColor() << std::endl;

		//std::cout << testCard->getCardType() << std::endl;

		//std::cout << testCard->getFactoryName() << std::endl;

		// debug spacing
		//std::cout << std::endl;


		std::cout << "Random test: " << std::endl;

		// random number checker that we could use for drawing a random card
		for (int i = 0; i < 10; i++)
		{

			// random algortithm from stackOverflow lol
			std::random_device seed;
			std::mt19937 gen{seed()}; // seed the generator
			std::uniform_int_distribution<> dist{1, 54}; // set min and max
			topOfDeck = dist(gen); // generate number

			std::cout << topOfDeck << std::endl;

		}

		std::random_device seed;
		std::mt19937 gen{seed()}; // seed the generator
		std::uniform_int_distribution<> dist{1, 54}; // set min and max
		topOfDeck = dist(gen); // generate number

		std::cout << "Current topOfDeck number: ";

		std::cout << topOfDeck << std::endl;

		// debug spacing
		std::cout << std::endl;

		std::cout << "Top of deck card type and color before dealCards(): " << std::endl;

		std::cout << dynamic_cast<Card*>(findByIndex(topOfDeck)->object())->getCardType() << std::endl;

		std::cout << dynamic_cast<Card*>(findByIndex(topOfDeck)->object())->getCardColor() << std::endl;

		// debug spacing
		std::cout << std::endl;

		dealCards();

		std::cout << "Top of deck card type and color after dealCards(): " << std::endl;

		std::cout << dynamic_cast<Card*>(findByIndex(topOfDeck)->object())->getCardType() << std::endl;

		std::cout << dynamic_cast<Card*>(findByIndex(topOfDeck)->object())->getCardColor() << std::endl;

		whoTurn = 1;

	}
}

void GameController::drawCard(int player)
{

	// front of drawPile
	Card* newCard = dynamic_cast<Card*>(findByIndex(topOfDeck));

	// put another random card on top of the deck 
		// because it was just drawn
	std::random_device seed;
	std::mt19937 gen{seed()}; // seed the generator
	std::uniform_int_distribution<> dist{1, 54}; // set min and max
	topOfDeck = dist(gen); // generate number

	switch (player)
	{
	case 1:
		player1Pile->addTail(newCard);

		std::cout << "Player 1 hand: " << std::endl;

		for (int i = 0; i < player1Pile->entries(); i++)
		{

			std::cout << dynamic_cast<Card*>(player1Pile->getPosition(i))->getCardType() << std::endl;

			std::cout << dynamic_cast<Card*>(player1Pile->getPosition(i))->getCardColor() << std::endl;
		}
		
		whoTurn = 2;

		break;
	case 2:
		player2Pile->addTail(newCard);

		whoTurn = 3;

		break;
	case 3:
		player3Pile->addTail(newCard);

		whoTurn = 4;

		break;
	case 4:
		player4Pile->addTail(newCard);

		whoTurn = 5;

		break;
	case 5:
		player5Pile->addTail(newCard);

		whoTurn = 6;

		break;
	case 6:
		player6Pile->addTail(newCard);
		
		whoTurn = 7;

		break;
	case 7:
		player7Pile->addTail(newCard);

		whoTurn = 8;

		break;
	case 8:
		player8Pile->addTail(newCard);

		whoTurn = 9;

		break;
	case 9:
		player9Pile->addTail(newCard);

		whoTurn = 10;

		break;
	case 10:
		player10Pile->addTail(newCard);

		whoTurn = 1;

		break;
	default:
		break;
	}

	// *** This whole concept might be unncessary because of the random variable i. 
		// Only if we want ot introduced a finite stack of cards, but why? who wants to do that? *** 

	// simply putting front() or 0 index as a parameter did not work. erase() wants something specific. 
		// hopefully this removes the front of the drawPile, assuming we are using a sort of shuffled stack for it in the front of vector will always be what is displayed and used during gameplay
	//drawPile.erase(drawPile.begin());
	
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
		for (int j = 0; j < numPlayers - 1; j++)
		{
			drawCard(j);  // using drawCard to give the card to player j
		}
	}
}

void GameController::setPlayerCount(int num)
{
	numPlayers = num;
}

void GameController::copyData(const GameController& org, const bool)
{
	BaseClass::copyData(org);
}



