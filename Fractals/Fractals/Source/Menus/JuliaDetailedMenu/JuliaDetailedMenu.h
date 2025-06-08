#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class JuliaDetailedMenu : public ImGuiWindow
{
	public:
		void Render() override;

	private:
		void RenderConstantControls();
};
