#include "Player.hpp"

IMPLEMENT_SUBCLASS(Player, "Player")
EMPTY_SLOTTABLE(Player)
EMPTY_DELETEDATA(Player)

// EVENT HANDLER

Player::Player()
{
	STANDARD_CONSTRUCTOR()
}

Player::Player(int newPlayerNum, float newCardXPos, float newCardYPos)	
{
	playerNum =newPlayerNum;
	cardXPos = newCardXPos;
	cardYPos = newCardYPos;
	hand = new mixr::base::PairStream();
	STANDARD_CONSTRUCTOR()
}

void Player::copyData(const Player& org, const bool)
{
	BaseClass::copyData(org);
	playerNum = org.playerNum;
	myTurn = org.myTurn;
	cardXPos = org.cardXPos;
	cardYPos = org.cardYPos;
	hand = org.hand;
	currentCard = org.currentCard;
}

void Player::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void Player::updateData(const double dt)
{
	BaseClass::updateData(dt);
}

void Player::reset()
{
	BaseClass::reset();
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
	for (int i = 1; i < hand->entries()+1; i++)
	{
		std::cout << "Card " << i << ": " << dynamic_cast<Card*>(hand->getPosition(i)->object())->getCardColor() << " "
			<< dynamic_cast<Card*>(hand->getPosition(i)->object())->getCardType() << std::endl;
	} 
}