#include "Station.hpp"

#include "mixr/ui/glut/GlutDisplay.hpp"

IMPLEMENT_SUBCLASS(Station, "Station")
EMPTY_SLOTTABLE(Station)
EMPTY_DELETEDATA(Station)

Station::Station()
{
    STANDARD_CONSTRUCTOR()
}

void Station::copyData(const Station& org, const bool)
{
    BaseClass::copyData(org);
}

void Station::reset()
{
    BaseClass::reset();
}