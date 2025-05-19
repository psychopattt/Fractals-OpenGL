#include "MandelbrotDetailed.h"

#include <numbers>

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Shaders/Buffers/Texture/Texture.h"
#include "Shaders/ComputeShader/ComputeShader.h"
#include "Simulation/SimulationDrawer/SimulationDrawer.h"

MandelbrotDetailed::MandelbrotDetailed(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void MandelbrotDetailed::Initialize(int width, int height, unsigned int seed)
{
	using std::make_unique;

	Simulation::Initialize(width, height, seed);

	simDrawer = make_unique<SimulationDrawer>();
	texture = make_unique<Texture>(width, height);

	mandelbrotShader = make_unique<ComputeShader>("MandelbrotDetailed", width, height);
	mandelbrotShader->SetTextureBinding("dataTexture", texture->GetId());
	mandelbrotShader->SetUniform("size", width, height);
}

void MandelbrotDetailed::Restart()
{
	texture->Clear();
}

void MandelbrotDetailed::ComputeComplexExp(float& real, float& image)
{
	float realExp = expf(real);
	real = cosf(image) * realExp;
	image = sinf(image) * realExp;
}

void MandelbrotDetailed::ComputeLightDirection(float& x, float& y)
{
	x = 0;
	y = FractalSettings::LightAngle * 2 * std::numbers::pi_v<float> / 360;
	ComputeComplexExp(x, y);
}

void MandelbrotDetailed::Execute()
{
	float lightDirectionX, lightDirectionY;
	ComputeLightDirection(lightDirectionX, lightDirectionY);
	mandelbrotShader->SetUniform("lightDirection", lightDirectionX, lightDirectionY);

	mandelbrotShader->SetUniform("lightHeight", FractalSettings::LightHeight);
	mandelbrotShader->SetUniform("oddIterationsTint", FractalSettings::OddIterationsTint);
	mandelbrotShader->SetUniform("evenIterationsTint", FractalSettings::EvenIterationsTint);

	mandelbrotShader->SetUniform("maxIterations", FractalSettings::MaxIterations);
	mandelbrotShader->SetUniform("scale", TransformSettings::ComputedScaleX, TransformSettings::ComputedScaleY);
	mandelbrotShader->SetUniform("pan", TransformSettings::ComputedPanX, TransformSettings::ComputedPanY);
	mandelbrotShader->Execute();
}

void MandelbrotDetailed::Draw()
{
	simDrawer->Draw(texture.get());
}
