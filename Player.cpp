#include "Player.hpp"

IMPLEMENT_SUBCLASS(Player, "Player")
EMPTY_SLOTTABLE(Player)
EMPTY_DELETEDATA(Player)

// EVENT HANDLER

Player::Player(int newPlayerNum, float newCardXPos, float newCardYPos) :
	playerNum(newPlayerNum), cardXPos(newCardXPos), cardYPos(newCardYPos)
{
	STANDARD_CONSTRUCTOR()
}

void Player::addCard(mixr::base::Pair* card)
{
	if(card != nullptr)
		hand->put(card);
}

void Player::removeCard(mixr::base::Pair* card)
{
	if(card != nullptr)
		hand->remove(card);
}

void Player::showHand()
{
	for (int i = 1; i < hand->entries(); i++)
	{
		std::cout << "Card " << i << ": " << dynamic_cast<Card*>(hand->getPosition(i)->object())->getCardType() << " "
			<< dynamic_cast<Card*>(hand->getPosition(i)->object())->getCardColor() << std::endl;
	} 
}