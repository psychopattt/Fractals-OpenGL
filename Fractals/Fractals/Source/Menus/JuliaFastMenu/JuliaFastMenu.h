#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class JuliaFastMenu : public ImGuiWindow
{
	public:
		void Render() override;
	
	private:
		void RenderConstantControls();
};
