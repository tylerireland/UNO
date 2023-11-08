#include "GameController.hpp"

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
		// it does not like using -> and only likes the "." but I want to avoid object slicing and use pointers, not and instance dependent access function. What do?? 
	if (drawPile.front()->getCardType() == card->getCardType())
	{
		return true;
	}
	if (drawPile.front()->getCardColor() == card->getCardColor())
	{
		return true;
	}

}

void GameController::drawCard()
{
	Card* newCard = drawPile.front();

	// there has to be a better way to do this
		// 

	if (whosTurn == 1)
	{
		player1Pile.push_back(newCard);
	}
	if (whosTurn == 2)
	{
		player2Pile.push_back(newCard);
	}
	if (whosTurn == 3)
	{
		player3Pile.push_back(newCard);
	}
	if (whosTurn == 4)
	{
		player4Pile.push_back(newCard);
	}
	if (whosTurn == 5)
	{
		player5Pile.push_back(newCard);
	}
	if (whosTurn == 6)
	{
		player6Pile.push_back(newCard);
	}
	if (whosTurn == 7)
	{
		player7Pile.push_back(newCard);
	}
	if (whosTurn == 8)
	{
		player8Pile.push_back(newCard);
	}
	if (whosTurn == 9)
	{
		player9Pile.push_back(newCard);
	}
	if (whosTurn == 10)
	{
		player10Pile.push_back(newCard);
	}

	// simply putting front() or 0 index did not work. erase() wants something specific. 
		// hopefully this removes the front of the drawPile, assuming we are using a sort of shuffled stack for it in the front of vector will always be what is displayed and used during gameplay
	drawPile.erase(drawPile.begin());
}

std::vector<Card*> GameController::shuffleCards(std::vector<Card*> pile)
{
	int size = pile.size();
	
	// algorithm to swap that may or may not work
		// iter_swap is supposed swap two elements when give two interators
	for (int i = 0; i < size - 1; i++) // we iterate through the size of the pile
	{
		int j = i + rand() % (size - i); // j is the current iterator i PLUS a random nunber modulus the pile size, which gives us a random element
		iter_swap(pile.begin() + i, pile.begin() + j); // then the element at i is swapped with the element at j 
	}
	// i found this through the algorithm library, so we'll see if this even works. 
	// there very well might be a much easier way to shuffle the cards, but this seemed fun to explore 

	// not sure if this would work but holy crap am I tired right now
	return pile;
}

void GameController::copyData(const GameController& org, const bool)
{
	BaseClass::copyData(org);
}



