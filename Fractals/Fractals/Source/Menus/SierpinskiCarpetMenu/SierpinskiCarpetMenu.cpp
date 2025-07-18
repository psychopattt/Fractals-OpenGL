#include "SierpinskiCarpetMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void SierpinskiCarpetMenu::Render()
{
	SeparatorText("Depth");
	InputScalar(
		"##inputDepth", ImGuiDataType_U32, &FractalSettings::MaxDepth,
		&FractalSettings::DepthStep, &FractalSettings::DepthStepFast
	);

	SeparatorText("Gradient Location");
	Checkbox("Invert", &FractalSettings::GradientInvert);

	SeparatorText("Gradient Brightness");
	SliderFloat("##sliderBrightness", &FractalSettings::GradientBrightness, 0, 1);

	SeparatorText("Gradient Repetition");
	DragScalar(
		"##dragRepetition", ImGuiDataType_Double,
		&FractalSettings::GradientRepetition, 0.005f, NULL, NULL, "%.2f"
	);
}
