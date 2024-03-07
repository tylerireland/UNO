#ifndef __GameDisplay_H__
#define __GameDisplay_H__

#include "Station.hpp"
#include "mixr/ui/glut/GlutDisplay.hpp"
#include "Pager.hpp"
#include <GL/glut.h>
#include "GameController.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/graphics/Page.hpp"
#include "mixr/base/Component.hpp"
#include <string>


class GameDisplay : public mixr::glut::GlutDisplay
{
	DECLARE_SUBCLASS(GameDisplay, mixr::glut::GlutDisplay)

public:
	GameDisplay();

	mixr::simulation::Simulation* getSimulation();
	mixr::simulation::Station* getStation();

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	
	void reset() final;
	void buttonEvent(const int b) final;

	bool event(const int event, mixr::base::Object* const obj = nullptr) override;

	bool onSendCard(mixr::base::String* textureName);
	bool onUpdatePlayerNum(mixr::base::Number* playerNumber);
	bool onUpdatePlayerTurnNum(mixr::base::Number* playerTurnNum);

private:

	int currentCard{1};
	SendData currentCardSD{};
	SendData playerNumSD{};
	SendData playerTurnNumSD{};

	mixr::base::safe_ptr<mixr::simulation::Station> stn;

};

#endif