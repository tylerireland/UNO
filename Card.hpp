#ifndef CARD_H
#define CARD_H

#include "mixr/graphics/Graphic.hpp"
#include <string>

/*
* setSlotType() - slot function to set the type
* setType() - sets the type of card (numbered, action, wild)
* setSlotColor() - slot function to set the color
* setColor() - sets the color of the card (Red, Blue, Green, Yellow)
* 
*/


class Card final : public mixr::graphics::Graphic
{
	DECLARE_SUBCLASS(Card, mixr::graphics::Graphic)

public:

	Card();

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	void reset() final;
	
	std::string getColor() { return color; }
	std::string getType() { return type; }

	void setType(const std::string newType) { type = newType; }
	void setColor(const std::string newColor) { color = newColor; }

private:

	std::string type;
	std::string color;

	bool setSlotType(const mixr::base::String* const);

	bool setSlotColor(const mixr::base::String* const);
	
};

#endif