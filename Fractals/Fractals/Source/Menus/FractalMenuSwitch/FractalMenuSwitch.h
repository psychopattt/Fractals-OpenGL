#pragma once

#include <memory>

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class FractalMenuSwitch : public ImGuiWindow
{
	public:
		void Initialize() override;
		void Render() override;

	private:
		void SwitchActiveMenu();
		void SwitchActiveFractal();

		std::unique_ptr<ImGuiWindow> activeMenu;
};
