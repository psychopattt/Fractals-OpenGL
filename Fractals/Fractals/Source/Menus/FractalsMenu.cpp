#include "FractalsMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void FractalsMenu::Render()
{
	if (Begin("Settings"))
	{
		if (CollapsingHeader("Fractals"))
		{
			PushItemWidth(-1);
			SeparatorText("Max Iterations");
			DragScalar("##dragMaxIterations", ImGuiDataType_U32, &FractalSettings::MaxIterations, 0.5f);
			PopItemWidth();
		}
	}

	End();
}
