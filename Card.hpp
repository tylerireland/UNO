#ifndef CARD_H
#define CARD_H

#include "mixr/graphics/Translator.hpp"
#include <string>

/*
* setSlotType() - slot function to set the type
* setType() - sets the type of card (numbered, action, wild)
* setSlotColor() - slot function to set the color
* setColor() - sets the color of the card (Red, Blue, Green, Yellow)
* 
*/


class Card final : public mixr::graphics::Translator
{
	DECLARE_SUBCLASS(Card, mixr::graphics::Translator)

public:

	Card();

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	void reset() final;
	
	std::string getCardColor() { return cardColor; }
	std::string getCardType() { return cardType; }

	void setCardType(std::string newType) { cardType = newType; }
	void setCardColor(std::string newColor) { cardColor = newColor; }

private:

	std::string cardType;
	std::string cardColor;

	bool setSlotCardType(const mixr::base::String* const);

	bool setSlotCardColor(const mixr::base::String* const);
	
};

#endif