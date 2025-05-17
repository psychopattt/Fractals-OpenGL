#include "Settings/TransformSettings.h"
#include "Simulation/Fractals.h"
#include "Menus/FractalsMenu.h"
#include "OCSFW.h"

int main()
{
	TransformSettings::MaxUiZoom = 16000;
	TransformSettings::ApplyTransforms = false;
	Fractals simulation = Fractals(1024, 1024);

	FractalsMenu fractalsMenu = FractalsMenu();
	ImGuiWindow* menus[] = { &fractalsMenu };

	OCSFW(&simulation)
		.WithTitle("Fractals")
		.WithMenus(menus, std::size(menus))
		.Run();

	return EXIT_SUCCESS;
}
