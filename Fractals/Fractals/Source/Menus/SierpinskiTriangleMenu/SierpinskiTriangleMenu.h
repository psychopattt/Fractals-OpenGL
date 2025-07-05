#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class SierpinskiTriangleMenu : public ImGuiWindow
{
	public:
		void Render() override;

	private:
		void RenderGradientLocationControls();
};
