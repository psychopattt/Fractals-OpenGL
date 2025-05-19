#include "MandelbrotFast.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Shaders/Buffers/Texture/Texture.h"
#include "Shaders/ComputeShader/ComputeShader.h"
#include "Simulation/SimulationDrawer/SimulationDrawer.h"

MandelbrotFast::MandelbrotFast(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void MandelbrotFast::Initialize(int width, int height, unsigned int seed)
{
	using std::make_unique;

	Simulation::Initialize(width, height, seed);

	simDrawer = make_unique<SimulationDrawer>();
	texture = make_unique<Texture>(width, height);

	mandelbrotShader = make_unique<ComputeShader>("MandelbrotFast", width, height);
	mandelbrotShader->SetTextureBinding("dataTexture", texture->GetId());
	mandelbrotShader->SetUniform("size", width, height);
}

void MandelbrotFast::Restart()
{
	texture->Clear();
}

void MandelbrotFast::Execute()
{
	mandelbrotShader->SetUniform("maxIterations", FractalSettings::MaxIterations);
	mandelbrotShader->SetUniform("scale", TransformSettings::ComputedScaleX, TransformSettings::ComputedScaleY);
	mandelbrotShader->SetUniform("pan", TransformSettings::ComputedPanX, TransformSettings::ComputedPanY);
	mandelbrotShader->Execute();
}

void MandelbrotFast::Draw()
{
	simDrawer->Draw(texture.get());
}
