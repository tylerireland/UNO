#ifndef __GameDisplay_H__
#define __GameDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"
#include <string>

class GameDisplay : public mixr::glut::GlutDisplay
{
	DECLARE_SUBCLASS(GameDisplay, mixr::glut::GlutDisplay)


public:
	GameDisplay();

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	bool event(const int event, mixr::base::Object* const obj = nullptr) override;
	void reset() final;

private:


};

#endif