#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class NewtonFractalMenu : public ImGuiWindow
{
	public:
		void Render() override;

	private:
		void RenderRootsControls();
		void RenderColorsControls();
		static constexpr unsigned int rootStep = 1;
};
