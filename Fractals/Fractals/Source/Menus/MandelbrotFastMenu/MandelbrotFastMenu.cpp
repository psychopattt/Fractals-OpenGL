#include "MandelbrotFastMenu.h"

#include <string>

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Simulation/SimulationMath/SimulationMath.h"
#include "Settings/LogString/LogString.h"
#include "Settings/MainSettings.h"

using namespace ImGui;

void MandelbrotFastMenu::Render()
{
	SeparatorText("Max Iterations");
	DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::MaxIterations, 0.5f);

	RenderPositionInputs();
	RenderPositionButtons();
}

void MandelbrotFastMenu::RenderPositionInputs()
{
	SeparatorText("Position");

	double position[2] = { };
	ComputeFractalPosition(position[0], position[1]);

	float dragSpeed = ComputePositionDragSpeed();
	int displayedDecimals = ComputePositionDisplayedDecimals(position[0], position[1]);
	std::string format = "%." + std::to_string(displayedDecimals) + "f";

	bool positionModified = DragScalarN(
		"##dragPosition", ImGuiDataType_Double, position, std::size(position), dragSpeed,
		&FractalSettings::MinPosition, &FractalSettings::MaxPosition, format.c_str(),
		ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_WrapAround
	);

	if (positionModified)
		UpdateSimulationPosition(position[0], position[1]);
}

float MandelbrotFastMenu::ComputePositionDragSpeed()
{
	double scaledZoom = SimulationMath::ScaleZoom(TransformSettings::Zoom);
	double dragSpeedAtZoom = 0.003 / scaledZoom;

	return static_cast<float>(dragSpeedAtZoom);
}

int MandelbrotFastMenu::ComputePositionDisplayedDecimals(double positionX, double positionY)
{
	float charWidth = CalcTextSize("0").x;
	int integerChars = 2 + (positionX < 0 || positionY < 0);
	float numberWidth = (GetItemRectSize().x - GetStyle().ItemInnerSpacing.x) / 2;
	float decimalsWidth = std::max(0.0f, numberWidth - (integerChars * charWidth));

	return std::min(17, static_cast<int>(decimalsWidth / charWidth));
}

void MandelbrotFastMenu::RenderPositionButtons()
{
	float buttonWidth = (GetItemRectSize().x - GetStyle().ItemSpacing.x) / 2;

	RenderPositionCopyButton(buttonWidth);
	SameLine();
	RenderPositionPasteButton(buttonWidth);
}

void MandelbrotFastMenu::RenderPositionCopyButton(float buttonWidth)
{
	if (Button("Copy", ImVec2(buttonWidth, 0)))
	{
		double positionX, positionY;
		ComputeFractalPosition(positionX, positionY);

		char buffer[42];
		snprintf(buffer, sizeof(buffer), "%.17f,%.17f", positionX, positionY);
		SetClipboardText(buffer);
	}
}

void MandelbrotFastMenu::RenderPositionPasteButton(float buttonWidth)
{
	if (Button("Paste", ImVec2(buttonWidth, 0)))
	{
		const char* clipboardChars = GetClipboardText();
		std::string clipboard = clipboardChars != NULL ? clipboardChars : "";

		try
		{
			size_t delimiterPosition = clipboard.find(',');
			double positionX = std::stod(clipboard.substr(0, delimiterPosition));
			double positionY = std::stod(clipboard.substr(delimiterPosition + 1));
			UpdateSimulationPosition(positionX, positionY);
		}
		catch (...)
		{
			MainSettings::Log << "Mandelbrot Error - Failed to parse position\n" <<
				"Clipboard content: " << clipboard << "\n\n";
		}
	}
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
