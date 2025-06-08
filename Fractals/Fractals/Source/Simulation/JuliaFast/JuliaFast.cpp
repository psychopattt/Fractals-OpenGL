#include "JuliaFast.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Shaders/Buffers/Texture/Texture.h"
#include "Shaders/ComputeShader/ComputeShader.h"
#include "Simulation/SimulationDrawer/SimulationDrawer.h"

JuliaFast::JuliaFast(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void JuliaFast::Initialize(int width, int height, unsigned int seed)
{
	using std::make_unique;

	Simulation::Initialize(width, height, seed);

	simDrawer = make_unique<SimulationDrawer>();
	texture = make_unique<Texture>(width, height);

	juliaShader = make_unique<ComputeShader>("JuliaFast", width, height);
	juliaShader->SetTextureBinding("dataTexture", texture->GetId());
	juliaShader->SetUniform("size", width, height);
}

void JuliaFast::Restart()
{
	texture->Clear();
}

void JuliaFast::Execute()
{
	juliaShader->SetUniform("maxIterations", FractalSettings::MaxIterations);
	juliaShader->SetUniform("constant", FractalSettings::ConstantX, FractalSettings::ConstantY);
	juliaShader->SetUniform("scale", TransformSettings::ComputedScaleX, TransformSettings::ComputedScaleY);
	juliaShader->SetUniform("pan", TransformSettings::ComputedPanX, TransformSettings::ComputedPanY);
	juliaShader->Execute();
}

void JuliaFast::Draw()
{
	simDrawer->Draw(texture.get());
}
