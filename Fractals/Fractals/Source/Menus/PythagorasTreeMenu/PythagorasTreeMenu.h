#pragma once

#include "Interface/ImGui/ImGuiWindow/ImGuiWindow.h"

class PythagorasTreeMenu : public ImGuiWindow
{
	public:
		void Initialize() override;
		void Render() override;

	private:
		static constexpr unsigned int orderStep = 1;
		static constexpr unsigned int orderStepFast = 3;
		static inline bool defaultSettingsApplied = false;
};
