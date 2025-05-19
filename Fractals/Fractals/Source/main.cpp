#include "Simulation/FractalSimulationSwitch/FractalSimulationSwitch.h"
#include "Settings/TransformSettings.h"
#include "Menus/FractalsMenu.h"
#include "OCSFW.h"

int main()
{
	TransformSettings::MaxUiZoom = 16000;
	TransformSettings::ApplyTransforms = false;
	FractalSimulationSwitch simulation = FractalSimulationSwitch(1024, 1024);

	FractalsMenu fractalsMenu = FractalsMenu();
	ImGuiWindow* menus[] = { &fractalsMenu };

	OCSFW(&simulation)
		.WithTitle("Fractals")
		.WithMenus(menus, std::size(menus))
		.Run();

	return EXIT_SUCCESS;
}
