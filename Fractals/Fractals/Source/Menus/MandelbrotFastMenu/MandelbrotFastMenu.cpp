#include "MandelbrotFastMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void MandelbrotFastMenu::Render()
{
	SeparatorText("Max Iterations");
	DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::MaxIterations, 0.5f);
}
