#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class MandelbrotFastMenu : public ImGuiWindow
{
	public:
		void Render() override;

	private:
		void RenderPositionInputs();
		float ComputePositionDragSpeed();
		int ComputePositionDisplayedDecimals(double positionX, double positionY);
		void RenderPositionButtons();
		void RenderPositionCopyButton(float buttonWidth);
		void RenderPositionPasteButton(float buttonWidth);

		void ComputeFractalPosition(double& positionX, double& positionY);
		double ComputeFractalPositionAxis(double simulationPosition);
		void UpdateSimulationPosition(double fractalPositionX, double fractalPositionY);
		long long ComputeSimulationPositionAxis(double fractalPosition);
};
