#include "JuliaDetailedMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void JuliaDetailedMenu::Render()
{
	SeparatorText("Max Iterations");
	DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::MaxIterations, 0.5f);

	RenderConstantControls();

	SeparatorText("Odd Iterations Tint");
	DragFloat("##dragOddIterationsTint", &FractalSettings::OddIterationsTint, 0.01f, -1, 100, "%.2f");

	SeparatorText("Even Iterations Tint");
	DragFloat("##dragEvenIterationsTint", &FractalSettings::EvenIterationsTint, 0.01f, -1, 100, "%.2f");

	SeparatorText("Light Height");
	SliderFloat("##sliderLightHeight", &FractalSettings::LightHeight, 0, 6, "%.2f");

	SeparatorText("Light Angle");
	DragFloat("##dragLightAngle", &FractalSettings::LightAngle, 0.5f, 0, 360, "%.1f", ImGuiSliderFlags_WrapAround);
}

void JuliaDetailedMenu::RenderConstantControls()
{
	SeparatorText("Constant");
	double constant[] = { FractalSettings::ConstantX, FractalSettings::ConstantY };

	bool constantModified = DragScalarN(
		"##dragConstant", ImGuiDataType_Double, constant, sizeof(constant) / sizeof(constant[0]),
		0.000001f, &FractalSettings::MinConstant, &FractalSettings::MaxConstant, "%.8f"
	);

	if (constantModified)
	{
		FractalSettings::ConstantX = constant[0];
		FractalSettings::ConstantY = constant[1];
	}
}
