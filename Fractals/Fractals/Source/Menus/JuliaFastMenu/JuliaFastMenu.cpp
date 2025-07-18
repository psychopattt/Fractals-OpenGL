#include "JuliaFastMenu.h"

#include <string>

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Simulation/SimulationMath/SimulationMath.h"
#include "Settings/LogString/LogString.h"
#include "Settings/MainSettings.h"

using namespace ImGui;

void JuliaFastMenu::Render()
{
	SeparatorText("Max Iterations");
	DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::MaxIterations, 0.5f);

	RenderConstantInputs();
	RenderConstantButtons();
}

void JuliaFastMenu::RenderConstantInputs()
{
	SeparatorText("Constant");

	float dragSpeed = ComputeConstantDragSpeed();
	double constant[] = { FractalSettings::ConstantX, FractalSettings::ConstantY };
	std::string format = "%." + std::to_string(ComputeConstantDisplayedDecimals()) + "f";

	bool constantModified = DragScalarN(
		"##dragConstant", ImGuiDataType_Double, constant, std::size(constant), dragSpeed,
		&FractalSettings::MinPosition, &FractalSettings::MaxPosition, format.c_str(),
		ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_AlwaysClamp
	);
	
	if (constantModified)
	{
		FractalSettings::ConstantX = constant[0];
		FractalSettings::ConstantY = constant[1];
	}
}

float JuliaFastMenu::ComputeConstantDragSpeed()
{
	double scaledZoom = SimulationMath::ScaleZoom(TransformSettings::Zoom);
	double dragSpeedAtZoom = 0.000006 / scaledZoom;

	return static_cast<float>(dragSpeedAtZoom);
}

int JuliaFastMenu::ComputeConstantDisplayedDecimals()
{
	float charWidth = CalcTextSize("0").x;
	float numberWidth = (GetItemRectSize().x - GetStyle().ItemInnerSpacing.x) / 2;
	int integerChars = 2 + (FractalSettings::ConstantX < 0 || FractalSettings::ConstantY < 0);
	float decimalsWidth = std::max(0.0f, numberWidth - (integerChars * charWidth));

	return std::min(17, static_cast<int>(decimalsWidth / charWidth));
}

void JuliaFastMenu::RenderConstantButtons()
{
	float buttonWidth = (GetItemRectSize().x - GetStyle().ItemSpacing.x) / 2;

	RenderConstantCopyButton(buttonWidth);
	SameLine();
	RenderConstantPasteButton(buttonWidth);
}

void JuliaFastMenu::RenderConstantCopyButton(float buttonWidth)
{
	if (Button("Copy", ImVec2(buttonWidth, 0)))
	{
		char buffer[42];

		snprintf(
			buffer, sizeof(buffer), "%.17f,%.17f",
			FractalSettings::ConstantX, FractalSettings::ConstantY
		);

		SetClipboardText(buffer);
	}
}

void JuliaFastMenu::RenderConstantPasteButton(float buttonWidth)
{
	if (Button("Paste", ImVec2(buttonWidth, 0)))
	{
		const char* clipboardChars = GetClipboardText();
		std::string clipboard = clipboardChars != NULL ? clipboardChars : "";

		try
		{
			size_t delimiterPosition = clipboard.find(',');
			double constantX = std::stod(clipboard.substr(0, delimiterPosition));
			double constantY = std::stod(clipboard.substr(delimiterPosition + 1));

			FractalSettings::ConstantX = constantX;
			FractalSettings::ConstantY = constantY;
		}
		catch (...)
		{
			MainSettings::Log << "Julia Error - Failed to parse constant\n" <<
				"Clipboard content: " << clipboard << "\n\n";
		}
	}
}
