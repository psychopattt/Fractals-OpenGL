#include "MandelbrotFastMenu.h"

#include <string>

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"

using namespace ImGui;

void MandelbrotFastMenu::Render()
{
	SeparatorText("Max Iterations");
	DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::MaxIterations, 0.5f);

	RenderPositionInputs();
}

void MandelbrotFastMenu::RenderPositionInputs()
{
	SeparatorText("Position");

	double position[2] = { };
	ComputeFractalPosition(position[0], position[1]);

	int displayedDecimals = ComputePositionDisplayedDecimals(position[0], position[1]);
	std::string format = "%." + std::to_string(displayedDecimals) + "f";

	bool positionModified = DragScalarN(
		"##dragPosition", ImGuiDataType_Double, position, std::size(position), 0.000001f,
		&FractalSettings::MinPosition, &FractalSettings::MaxPosition, format.c_str(),
		ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_WrapAround
	);

	if (positionModified)
		UpdateSimulationPosition(position[0], position[1]);
}

void MandelbrotFastMenu::ComputeFractalPosition(double& positionX, double& positionY)
{
	positionX = ComputeFractalPositionAxis(static_cast<double>(TransformSettings::PanX));
	positionY = ComputeFractalPositionAxis(static_cast<double>(TransformSettings::PanY));
}

double MandelbrotFastMenu::ComputeFractalPositionAxis(double simulationPosition)
{
	return simulationPosition / TransformSettings::MaxPan * FractalSettings::MaxPosition;
}

void MandelbrotFastMenu::UpdateSimulationPosition(double fractalPositionX, double fractalPositionY)
{
	TransformSettings::PanX = ComputeSimulationPositionAxis(fractalPositionX);
	TransformSettings::PanY = ComputeSimulationPositionAxis(fractalPositionY);
}

long long MandelbrotFastMenu::ComputeSimulationPositionAxis(double fractalPosition)
{
	return llround(fractalPosition * TransformSettings::MaxPan / FractalSettings::MaxPosition);
}

int MandelbrotFastMenu::ComputePositionDisplayedDecimals(double positionX, double positionY)
{
	float charWidth = CalcTextSize("0").x;
	int integerChars = 2 + (positionX < 0 || positionY < 0);
	float numberWidth = (GetItemRectSize().x - GetStyle().ItemInnerSpacing.x) / 2;
	float decimalsWidth = std::max(0.0f, numberWidth - (integerChars * charWidth));

	return std::min(17, static_cast<int>(decimalsWidth / charWidth));
}
