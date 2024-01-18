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

//------------------------------------------------------------------------------
// reset() - this is our reset event, which will be called from the mainline
// by sending the base::Component::RESET_EVENT token.  Here we will set up
// our display
//------------------------------------------------------------------------------
void Station::reset()
{
    // this calls our Baseclass (simulation::Station -> reset)
    BaseClass::reset();
}