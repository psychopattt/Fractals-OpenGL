#pragma once

#include <memory>

#include "Simulation/Simulation.h"

using std::unique_ptr;

class JuliaDetailed : public Simulation
{
	public:
		JuliaDetailed(int width, int height, unsigned int seed = 0);
		void Initialize(int width, int height, unsigned int seed = 0) override;
		void Restart() override;
		void Execute() override;
		void Draw() override;

	private:
		void ComputeComplexExp(float& real, float& image);
		void ComputeLightDirection(float& x, float& y);

		unique_ptr<class Texture> texture;
		unique_ptr<class SimulationDrawer> simDrawer;
		unique_ptr<class ComputeShader> juliaShader;
};
