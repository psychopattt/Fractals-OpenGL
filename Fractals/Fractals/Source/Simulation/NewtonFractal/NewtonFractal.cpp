#include "NewtonFractal.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Shaders/Buffers/Texture/Texture.h"
#include "Shaders/ComputeShader/ComputeShader.h"
#include "Simulation/SimulationDrawer/SimulationDrawer.h"

NewtonFractal::NewtonFractal(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void NewtonFractal::Initialize(int width, int height, unsigned int seed)
{
	using std::make_unique;

	Simulation::Initialize(width, height, seed);

	simDrawer = make_unique<SimulationDrawer>();
	texture = make_unique<Texture>(width, height);

	newtonShader = make_unique<ComputeShader>("NewtonFractal", width, height);
	newtonShader->SetTextureBinding("dataTexture", texture->GetId());
	newtonShader->SetUniform("size", width, height);
}

void NewtonFractal::Restart()
{
	texture->Clear();
}

void NewtonFractal::Execute()
{
	newtonShader->SetUniform("scale", TransformSettings::ComputedScaleX, TransformSettings::ComputedScaleY);
	newtonShader->SetUniform("pan", TransformSettings::ComputedPanX, TransformSettings::ComputedPanY);
	newtonShader->SetUniform("roots", FractalSettings::Roots);
	newtonShader->SetUniform("maxIterations", FractalSettings::NewtonMaxIterations);
	newtonShader->SetUniform("colorMultiplier", FractalSettings::Roots / static_cast<float>(FractalSettings::ColorCount));
	newtonShader->SetUniform("colorShift", FractalSettings::ColorShift / 360);
	newtonShader->Execute();
}

void NewtonFractal::Draw()
{
	simDrawer->Draw(texture.get());
}
