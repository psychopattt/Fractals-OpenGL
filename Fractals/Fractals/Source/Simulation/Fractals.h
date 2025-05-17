#pragma once

#include <memory>

#include "Simulation/Simulation.h"

using std::unique_ptr;

class Fractals : public Simulation
{
	public:
		Fractals(int width, int height, unsigned int seed = 0);
		void Initialize(int width, int height, unsigned int seed = 0) override;
		void Restart() override;
		void Execute() override;
		void Draw() override;
		~Fractals();

	private:
		unique_ptr<class Texture> texture;
		unique_ptr<class SimulationDrawer> simDrawer;
		unique_ptr<class ComputeShader> mandelbrotShader;
};
