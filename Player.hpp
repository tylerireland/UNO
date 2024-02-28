#ifndef __Player_H__
#define __Player_H__

#include "mixr/base/Component.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/Pair.hpp"
#include "Card.hpp"

class Player : public mixr::base::Component
{
	DECLARE_SUBCLASS(Player, mixr::base::Component)

public:
	Player();
	Player(int playerNum, float cardXPos, float cardYPos);

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	void reset() final;

	// add card to the players hand
	void addCard(mixr::base::Pair* card);

	// remove card from the players hand
	void removeCard(mixr::base::Pair* card);

	// returns total cards  in players hand
	int getTotalCards() { return hand->entries(); }

	bool isMyTurn() { return myTurn; }

	void setTurn(bool turn) { myTurn = turn; }

	void showHand();

	int getPlayerNum() { return playerNum; }

private:

	// The players number (Player 1, 2, etc.)
	int playerNum = 0;

	// is it the players turn
	bool myTurn = false;

	// sets the location of the card on the Display
	float cardXPos;
	float cardYPos;

	// Players hand
	mixr::base::PairStream* hand{};

	// The current card displayed on the screen
	mixr::base::Pair* currentCard;




};

#endif

