#ifndef CARD_H
#define CARD_H

#include "mixr/graphics/Translator.hpp"
#include <string>

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