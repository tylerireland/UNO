#ifndef __Station_H__
#define __Station_H__

#include "mixr/simulation/Station.hpp"

namespace mixr {
    namespace glut { class GlutDisplay; }
}

class Station final : public mixr::simulation::Station
{
    DECLARE_SUBCLASS(Station, mixr::simulation::Station)

public:
    Station();

    void reset() final;

private:

};

#endif
