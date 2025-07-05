#include "FractalSimulationSwitch.h"

#include "Settings/FractalType.h"
#include "Settings/FractalSettings.h"
#include "../MandelbrotFast/MandelbrotFast.h"
#include "../MandelbrotDetailed/MandelbrotDetailed.h"
#include "../JuliaDetailed/JuliaDetailed.h"
#include "../JuliaFast/JuliaFast.h"
#include "../SierpinskiTriangle/SierpinskiTriangle.h"

FractalSimulationSwitch::FractalSimulationSwitch(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void FractalSimulationSwitch::SwitchActiveFractal()
{
	using std::make_unique;

	switch (FractalSettings::ActiveFractal)
	{
		case FractalType::MandelbrotFast:
			activeFractal = make_unique<MandelbrotFast>(width, height, seed);
			break;
		case FractalType::MandelbrotDetailed:
			activeFractal = make_unique<MandelbrotDetailed>(width, height, seed);
			break;
		case FractalType::JuliaFast:
			activeFractal = make_unique<JuliaFast>(width, height, seed);
			break;
		case FractalType::JuliaDetailed:
			activeFractal = make_unique<JuliaDetailed>(width, height, seed);
			break;
		case FractalType::SierpinskiTriangle:
			activeFractal = make_unique<SierpinskiTriangle>(width, height, seed);
			break;
	}

	activeFractal->Initialize();
}

void FractalSimulationSwitch::Initialize(int width, int height, unsigned int seed)
{
	Simulation::Initialize(width, height, seed);
	activeFractal->Initialize(width, height, seed);
}

void FractalSimulationSwitch::Restart()
{
	activeFractal->Restart();
}

void FractalSimulationSwitch::Execute()
{
	activeFractal->Execute();
}

void FractalSimulationSwitch::Draw()
{
	activeFractal->Draw();
}
