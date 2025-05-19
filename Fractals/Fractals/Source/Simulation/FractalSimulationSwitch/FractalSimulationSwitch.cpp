#include "FractalSimulationSwitch.h"

#include "Settings/FractalType.h"
#include "Settings/FractalSettings.h"
#include "../MandelbrotFast/MandelbrotFast.h"
#include "../MandelbrotDetailed/MandelbrotDetailed.h"

FractalSimulationSwitch::FractalSimulationSwitch(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void FractalSimulationSwitch::SwitchActiveFractal(bool initialize)
{
	if (activeFractalType != FractalSettings::ActiveFractal)
	{
		using std::make_unique;
		activeFractalType = FractalSettings::ActiveFractal;

		switch (activeFractalType)
		{
			case FractalType::MandelbrotFast:
				activeFractal = make_unique<MandelbrotFast>(width, height, seed);
				break;
			case FractalType::MandelbrotDetailed:
				activeFractal = make_unique<MandelbrotDetailed>(width, height, seed);
				break;
		}

		if (initialize)
			activeFractal->Initialize();
	}
}

void FractalSimulationSwitch::Initialize(int width, int height, unsigned int seed)
{
	Simulation::Initialize(width, height, seed);
	SwitchActiveFractal(false);
	activeFractal->Initialize(width, height, seed);
}

void FractalSimulationSwitch::Restart()
{
	SwitchActiveFractal();
	activeFractal->Restart();
}

void FractalSimulationSwitch::Execute()
{
	SwitchActiveFractal();
	activeFractal->Execute();
}

void FractalSimulationSwitch::Draw()
{
	SwitchActiveFractal();
	activeFractal->Draw();
}
