#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class MandelbrotFastMenu : public ImGuiWindow
{
	public:
		void Render() override;

	private:
		void RenderPositionInputs();
		void ComputeFractalPosition(double& positionX, double& positionY);
		double ComputeFractalPositionAxis(double simulationPosition);
		void UpdateSimulationPosition(double fractalPositionX, double fractalPositionY);
		long long ComputeSimulationPositionAxis(double fractalPosition);
		int ComputePositionDisplayedDecimals(double positionX, double positionY);
};
