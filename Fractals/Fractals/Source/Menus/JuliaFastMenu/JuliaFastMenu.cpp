#include "JuliaFastMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void JuliaFastMenu::Render()
{
	SeparatorText("Max Iterations");
	DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::MaxIterations, 0.5f);

	RenderConstantControls();
}

void JuliaFastMenu::RenderConstantControls()
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
