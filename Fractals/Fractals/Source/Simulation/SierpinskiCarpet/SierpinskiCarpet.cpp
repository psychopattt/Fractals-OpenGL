#include "SierpinskiCarpet.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Shaders/Buffers/Texture/Texture.h"
#include "Shaders/ComputeShader/ComputeShader.h"
#include "Simulation/SimulationDrawer/SimulationDrawer.h"

SierpinskiCarpet::SierpinskiCarpet(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void SierpinskiCarpet::Initialize(int width, int height, unsigned int seed)
{
	using std::make_unique;

	Simulation::Initialize(width, height, seed);

	simDrawer = make_unique<SimulationDrawer>();
	texture = make_unique<Texture>(width, height);

	sierpinskiShader = make_unique<ComputeShader>("SierpinskiCarpet", width, height);
	sierpinskiShader->SetTextureBinding("dataTexture", texture->GetId());
	sierpinskiShader->SetUniform("size", width, height);
}

void SierpinskiCarpet::Restart()
{
	texture->Clear();
}

void SierpinskiCarpet::Execute()
{
	sierpinskiShader->SetUniform("scale", TransformSettings::ComputedScaleX, TransformSettings::ComputedScaleY);
	sierpinskiShader->SetUniform("pan", TransformSettings::ComputedPanX, TransformSettings::ComputedPanY);
	sierpinskiShader->SetUniform("gradientBrightness", FractalSettings::GradientBrightness);
	sierpinskiShader->SetUniform("gradientRepetition", FractalSettings::GradientRepetition);
	sierpinskiShader->SetUniform("gradientInvert", FractalSettings::GradientInvert);
	sierpinskiShader->SetUniform("maxDepth", FractalSettings::MaxDepth);
	sierpinskiShader->Execute();
}

void SierpinskiCarpet::Draw()
{
	simDrawer->Draw(texture.get());
}
