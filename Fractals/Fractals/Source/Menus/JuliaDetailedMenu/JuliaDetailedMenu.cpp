#include "JuliaDetailedMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void JuliaDetailedMenu::Render()
{
	JuliaFastMenu::Render();

	SeparatorText("Odd Iterations Tint");
	DragFloat("##dragOddIterationsTint", &FractalSettings::OddIterationsTint, 0.01f, -1, 100, "%.2f");

	SeparatorText("Even Iterations Tint");
	DragFloat("##dragEvenIterationsTint", &FractalSettings::EvenIterationsTint, 0.01f, -1, 100, "%.2f");

	SeparatorText("Light Height");
	SliderFloat("##sliderLightHeight", &FractalSettings::LightHeight, 0, 6, "%.2f");

	SeparatorText("Light Angle");
	DragFloat("##dragLightAngle", &FractalSettings::LightAngle, 0.5f, 0, 360, "%.1f", ImGuiSliderFlags_WrapAround);
}
