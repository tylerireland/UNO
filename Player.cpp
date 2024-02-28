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

void Player::addCard(Pair* card)
{
	if(card != nullptr)
		hand->put(card);
}

void Player::removeCard(Pair* card)
{
	if(card != nullptr)
		hand->remove(card);
}