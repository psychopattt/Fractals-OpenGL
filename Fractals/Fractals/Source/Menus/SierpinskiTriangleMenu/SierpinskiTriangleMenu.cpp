#include "SierpinskiTriangleMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void SierpinskiTriangleMenu::Render()
{
	SeparatorText("Depth");
	InputScalar(
		"##inputDepth", ImGuiDataType_U32, &FractalSettings::MaxDepth,
		&FractalSettings::DepthStep, &FractalSettings::DepthStepFast
	);

	RenderGradientLocationControls();

	SeparatorText("Gradient Brightness");
	SliderFloat("##sliderBrightness", &FractalSettings::GradientBrightness, 0, 1);

	SeparatorText("Gradient Repetition");
	DragScalar(
		"##dragRepetition", ImGuiDataType_Double,
		&FractalSettings::GradientRepetition, 0.005f, NULL, NULL, "%.2f"
	);
}

void SierpinskiTriangleMenu::RenderGradientLocationControls()
{
	SeparatorText("Gradient Location");

	if (RadioButton("X", !FractalSettings::GradientAxis))
		FractalSettings::GradientAxis = false;

	SameLine();

	if (RadioButton("Y", FractalSettings::GradientAxis))
		FractalSettings::GradientAxis = true;

	SameLine(0, 30);

	Checkbox("Invert", &FractalSettings::GradientInvert);
}
