#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class JuliaFastMenu : public ImGuiWindow
{
	public:
		void Render() override;
	
	private:
		void RenderConstantInputs();
		float ComputeConstantDragSpeed();
		int ComputeConstantDisplayedDecimals();
		void RenderConstantButtons();
		void RenderConstantCopyButton(float buttonWidth);
		void RenderConstantPasteButton(float buttonWidth);
};
