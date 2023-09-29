#include "Card.hpp"
#include "mixr/base/String.hpp"

IMPLEMENT_SUBCLASS(Card, "Card")
EMPTY_DELETEDATA(Card)

BEGIN_SLOTTABLE(Card)
	"cardType",				// This is determine the type of card it will be
						// ONLY accepts "zero" to "nine", "reverse", "skip", "drawFour",
						//              "drawTwo", "wild", "swapHand"
	
	"cardColor",			// This will determine the color the card will be
						// ONLY accepts "red", "blue", "green", "yellow", "default" (for wilds)
END_SLOTTABLE(Card)

BEGIN_SLOT_MAP(Card)
	ON_SLOT(1, setSlotCardType, mixr::base::String)
	ON_SLOT(2, setSlotCardColor, mixr::base::String)
END_SLOT_MAP()

Card::Card()
{
	STANDARD_CONSTRUCTOR()
}

void Card::Card::copyData(const Card& org, const bool)
{
	BaseClass::copyData(org);
}

void Card::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void Card::updateData(const double dt)
{
	BaseClass::updateData(dt);
}

void Card::reset()
{
	BaseClass::reset();
}

bool Card::setSlotCardType(const mixr::base::String* const sobj)
{
	bool ok{};
	if (sobj != nullptr)
	{
		setCardType(sobj->getString());
		ok = true;
	}

	return ok;
}

bool Card::setSlotCardColor(const mixr::base::String* const cobj)
{
	bool ok{};
	if (cobj != nullptr)
	{
		setCardColor(cobj->getString());
		ok = true;
	}

	return ok;
}