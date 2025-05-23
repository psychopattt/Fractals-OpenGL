#include "Simulation/FractalSimulationSwitch/FractalSimulationSwitch.h"
#include "Menus/FractalMenuSwitch/FractalMenuSwitch.h"
#include "Settings/TransformSettings.h"
#include "OCSFW.h"

int main()
{
	TransformSettings::MaxUiZoom = 16000;
	TransformSettings::ApplyTransforms = false;

	FractalSimulationSwitch simulation = FractalSimulationSwitch(1024, 1024);
	FractalMenuSwitch menu = FractalMenuSwitch();
	ImGuiWindow* menus[] = { &menu };

	OCSFW(&simulation)
		.WithTitle("Fractals")
		.WithMenus(menus, std::size(menus))
		.Run();

	return EXIT_SUCCESS;
}
