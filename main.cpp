
#include "GameDisplay.hpp"
#include "Card.hpp"
#include "Pager.hpp"
#include "GameController.hpp"
#include "Station.hpp"

#include "mixr/base/Timers.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/edl_parser.hpp"
#include "mixr/base/Object.hpp"
#include "mixr/base/util/system_utils.hpp"

#include <string>
#include <GL/glut.h>

#include "mixr/base/factory.hpp"
#include "mixr/graphics/factory.hpp"
#include "mixr/instruments/factory.hpp"
#include "mixr/simulation/factory.hpp"
#include "mixr/ui/glut/factory.hpp"

const int frameRate{ 60 };
GameDisplay* display{};

void timerFunc(int)
{
    const double dt{ 1.0 / static_cast<double>(frameRate) };
    const int millis{ static_cast<int>(dt * 1000) };
    glutTimerFunc(millis, timerFunc, 1);

    mixr::base::Timer::updateTimers(static_cast<float>(dt));
    mixr::graphics::Graphic::flashTimer(static_cast<double>(dt));
    display->tcFrame(static_cast<double>(dt));
}

mixr::base::Object* factory(const std::string& name)
{
    mixr::base::Object* obj{};

    if (name == GameDisplay::getFactoryName())           obj = new GameDisplay();
    else if (name == Card::getFactoryName())             obj = new Card();
    else if (name == Pager::getFactoryName())            obj = new Pager();
    else if (name == GameController::getFactoryName())   obj = new GameController();
    else if (name == Station::getFactoryName())          obj = new Station();

    // framework libraries
    if (obj == nullptr) obj = mixr::simulation::factory(name);
    if (obj == nullptr) obj = mixr::instruments::factory(name);
    if (obj == nullptr) obj = mixr::graphics::factory(name);
    if (obj == nullptr) obj = mixr::glut::factory(name);
    if (obj == nullptr) obj = mixr::base::factory(name);

    return obj;
}
GameDisplay* builder(const std::string& filename)
{
    // read configuration file
    int num_errors{};
    mixr::base::Object* obj{mixr::base::edl_parser(filename, factory, &num_errors)};
    if (num_errors > 0) {
        std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // test to see if an object was created
    if (obj == nullptr) {
        std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
        std::exit(EXIT_FAILURE);
    } 

    // do we have a base::Pair, if so, point to object in Pair, not Pair itself
    const auto pair = dynamic_cast<mixr::base::Pair*>(obj);
    if (pair != nullptr) {
        obj = pair->object();
        obj->ref();
        pair->unref();
    }

    // try to cast to proper object, and check
    const auto display = dynamic_cast<GameDisplay*>(obj);
    if (display == nullptr) {
        std::cerr << "Invalid configuration file!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return display;
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    // default configuration filename
    std::string configFilename = "file0.edl";

    // parse arguments
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-f") {
            configFilename = argv[++i];
        }
    }

    // build a display
    display = builder(configFilename);

    // create a display window
    display->createWindow();

    // set timer
    const double dt{ 1.0 / static_cast<double>(frameRate) };
    const int millis{ static_cast<int>(dt * 1000) };
    glutTimerFunc(millis, timerFunc, 1);

    // main loop
    glutMainLoop();
    return 0;
}