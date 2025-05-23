#pragma once

#include <memory>

#include "Simulation/Simulation.h"

class FractalSimulationSwitch : public Simulation
{
	public:
		FractalSimulationSwitch(int width, int height, unsigned int seed = 0);
		void Initialize(int width, int height, unsigned int seed = 0) override;
		void Restart() override;
		void Execute() override;
		void Draw() override;

		void SwitchActiveFractal();

	private:
		std::unique_ptr<Simulation> activeFractal;
};
