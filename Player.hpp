#ifndef __Player_H__
#define __Player_H__

#include "mixr/base/Component.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/Pair.hpp"
#include "Card.hpp"

using namespace mixr;
using namespace base;

class Player : public Component
{
	DECLARE_SUBCLASS(Player, Component)

public:
	Player(int playerNum, float cardXPos, float cardYPos);

	// add card to the players hand
	void addCard(Pair* card);

	// remove card from the players hand
	void removeCard(Pair* card);

	// returns total cards  in players hand
	int getTotalCards() { return hand->entries(); }

	bool isMyTurn() { return myTurn; }

	void setTurn(bool turn) { myTurn = turn; }

private:

	// The players number (Player 1, 2, etc.)
	int playerNum = 0;

	// is it the players turn
	bool myTurn = false;

	// sets the location of the card on the Display
	float cardXPos;
	float cardYPos;

	// Players hand
	PairStream* hand{};

	// The current card displayed on the screen
	Pair* currentCard;




};

#endif

