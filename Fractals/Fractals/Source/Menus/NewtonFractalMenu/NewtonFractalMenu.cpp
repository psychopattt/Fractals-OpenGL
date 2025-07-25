#include "NewtonFractalMenu.h"

#include <cmath>

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void NewtonFractalMenu::Render()
{
	RenderRootsControls();

	SeparatorText("Max Iterations");
	DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::NewtonMaxIterations, 0.1f);

	RenderColorsControls();

	SeparatorText("Color Shift");
	DragFloat("##dragColorShift", &FractalSettings::ColorShift, 0.5f, 0, 360, "%.1f", ImGuiSliderFlags_WrapAround);
}

void NewtonFractalMenu::RenderRootsControls()
{
	SeparatorText("Roots");
	bool applyMaxColorCount = FractalSettings::ColorCount == FractalSettings::Roots;

	if (InputScalar("##inputRoots", ImGuiDataType_U32, &FractalSettings::Roots, &rootStep))
	{
		if (FractalSettings::Roots < 1)
			FractalSettings::Roots = 1;

		if (applyMaxColorCount || FractalSettings::ColorCount > FractalSettings::Roots)
			FractalSettings::ColorCount = FractalSettings::Roots;
	}
}

void NewtonFractalMenu::RenderColorsControls()
{
	SeparatorText("Colors");

	unsigned int min = 1;
	unsigned int values = static_cast<unsigned int>(ceilf(FractalSettings::Roots / 2.0f));
	unsigned int max = FractalSettings::Roots < 2 ? 1 : values + 1;
	unsigned int value = FractalSettings::ColorCount == FractalSettings::Roots ? max : FractalSettings::ColorCount;
	const char* format = value == max ? "Max" : "%d";
	
	bool updateRequired = SliderScalar(
		"##sliderColors", ImGuiDataType_U32, &value, &min, &max, format, ImGuiSliderFlags_AlwaysClamp
	) || FractalSettings::ColorCount == max && FractalSettings::ColorCount < FractalSettings::Roots;

	if (updateRequired)
		FractalSettings::ColorCount = value == max ? FractalSettings::Roots : value;
}
