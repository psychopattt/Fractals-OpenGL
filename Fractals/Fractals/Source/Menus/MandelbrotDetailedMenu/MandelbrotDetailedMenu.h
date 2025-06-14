#pragma once

#include "../MandelbrotFastMenu/MandelbrotFastMenu.h"

class MandelbrotDetailedMenu : public MandelbrotFastMenu
{
	public:
		void Render() override;
};
