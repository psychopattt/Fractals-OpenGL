#include "PythagorasTreeMenu.h"

#include "imgui/imgui.h"

#include "Settings/FractalSettings.h"

using namespace ImGui;

void PythagorasTreeMenu::Initialize()
{
	if (!defaultSettingsApplied)
	{
		defaultSettingsApplied = true;
		SetColorEditOptions(ImGuiColorEditFlags_PickerHueWheel);
	}
}

void PythagorasTreeMenu::Render()
{
	SeparatorText("Order");
	InputScalar("##inputOrder", ImGuiDataType_U32, &FractalSettings::TreeOrder, &orderStep, &orderStepFast);

	SeparatorText("Appearance");
	Checkbox("Merge Branches", &FractalSettings::MergeBranches);

	SeparatorText("Trunk Color");
	ColorEdit3("##editTrunkColor", FractalSettings::TrunkColor);

	SeparatorText("Leaves Color");
	ColorEdit3("##editLeavesColor", FractalSettings::LeavesColor);
}
