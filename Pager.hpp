#ifndef __Pager_H__
#define __Pager_H__

#include "mixr/graphics/Page.hpp"

class Pager final : public mixr::graphics::Page
{
	DECLARE_SUBCLASS(Pager, mixr::graphics::Page)

public:
	Pager();

	bool onEntry() final;
};

#endif
