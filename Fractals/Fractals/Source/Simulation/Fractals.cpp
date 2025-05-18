#include "Fractals.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Shaders/Buffers/Texture/Texture.h"
#include "Shaders/ComputeShader/ComputeShader.h"
#include "Simulation/SimulationDrawer/SimulationDrawer.h"

Fractals::Fractals(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void Fractals::Initialize(int width, int height, unsigned int seed)
{
	using std::make_unique;

	Simulation::Initialize(width, height, seed);
	
	simDrawer = make_unique<SimulationDrawer>();
	texture = make_unique<Texture>(width, height);

	mandelbrotShader = make_unique<ComputeShader>("MandelbrotFast", width, height);
	mandelbrotShader->SetTextureBinding("dataTexture", texture->GetId());
	mandelbrotShader->SetUniform("size", width, height);
}

void Fractals::Restart()
{
	texture->Clear();
}

void Fractals::Execute()
{
	mandelbrotShader->SetUniform("maxIterations", FractalSettings::MaxIterations);
	mandelbrotShader->SetUniform("scale", TransformSettings::ComputedScaleX, TransformSettings::ComputedScaleY);
	mandelbrotShader->SetUniform("pan", TransformSettings::ComputedPanX, TransformSettings::ComputedPanY);
	mandelbrotShader->Execute();
}

void Fractals::Draw()
{
	simDrawer->Draw(texture.get());
}

Fractals::~Fractals() { }
