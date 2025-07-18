#include "FractalMenuSwitch.h"

#include "imgui/imgui.h"

#include "Settings/FractalType.h"
#include "Simulation/Simulation.h"
#include "Settings/MainSettings.h"
#include "Settings/FractalSettings.h"
#include "Simulation/FractalSimulationSwitch/FractalSimulationSwitch.h"
#include "../MandelbrotDetailedMenu/MandelbrotDetailedMenu.h"
#include "../MandelbrotFastMenu/MandelbrotFastMenu.h"
#include "../JuliaDetailedMenu/JuliaDetailedMenu.h"
#include "../JuliaFastMenu/JuliaFastMenu.h"
#include "../SierpinskiCarpetMenu/SierpinskiCarpetMenu.h"
#include "../SierpinskiTriangleMenu/SierpinskiTriangleMenu.h"

using namespace ImGui;

void FractalMenuSwitch::SwitchActiveMenu()
{
	using std::make_unique;

	switch (FractalSettings::ActiveFractal)
	{
		case FractalType::MandelbrotFast:
			activeMenu = make_unique<MandelbrotFastMenu>();
			break;
		case FractalType::MandelbrotDetailed:
			activeMenu = make_unique<MandelbrotDetailedMenu>();
			break;
		case FractalType::JuliaFast:
			activeMenu = make_unique<JuliaFastMenu>();
			break;
		case FractalType::JuliaDetailed:
			activeMenu = make_unique<JuliaDetailedMenu>();
			break;
		case FractalType::SierpinskiCarpet:
			activeMenu = make_unique<SierpinskiCarpetMenu>();
			break;
		case FractalType::SierpinskiTriangle:
			activeMenu = make_unique<SierpinskiTriangleMenu>();
			break;
	}

	activeMenu->Initialize();
}

void FractalMenuSwitch::SwitchActiveFractal()
{
	SwitchActiveMenu();
	static_cast<FractalSimulationSwitch*>(MainSettings::Sim)->SwitchActiveFractal();
}

void FractalMenuSwitch::Initialize()
{
	SwitchActiveFractal();
}

void FractalMenuSwitch::Render()
{
	SetNextWindowPos(ImVec2(270, 10), ImGuiCond_FirstUseEver);
	SetNextWindowSize(ImVec2(275, -1), ImGuiCond_FirstUseEver);

	if (Begin("Fractal Settings"))
	{
		PushItemWidth(-1);
		SeparatorText("Fractal Type");

		if (Combo("##comboFractalType", (int*)&FractalSettings::ActiveFractal, FractalTypeLabels))
		{
			SwitchActiveFractal();
			SetWindowSize(ImVec2(GetWindowWidth(), -1));
		}
		
		activeMenu->Render();
		PopItemWidth();
	}

	End();
}
