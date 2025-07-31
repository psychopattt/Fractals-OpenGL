#include "PythagorasTree.h"

#include "Settings/FractalSettings.h"
#include "Settings/TransformSettings.h"
#include "Shaders/Buffers/Texture/Texture.h"
#include "Shaders/ComputeShader/ComputeShader.h"
#include "Simulation/SimulationDrawer/SimulationDrawer.h"

PythagorasTree::PythagorasTree(int width, int height, unsigned int seed) :
	Simulation(width, height, seed) { };

void PythagorasTree::Initialize(int width, int height, unsigned int seed)
{
	using std::make_unique;

	Simulation::Initialize(width, height, seed);

	simDrawer = make_unique<SimulationDrawer>();
	texture = make_unique<Texture>(width, height);

	treeShader = make_unique<ComputeShader>("PythagorasTree", width, height);
	treeShader->SetTextureBinding("dataTexture", texture->GetId());
	treeShader->SetUniform("size", width, height);
}

void PythagorasTree::Restart()
{
	texture->Clear();
}

void PythagorasTree::Execute()
{
	using FractalSettings::TrunkColor, FractalSettings::LeavesColor;

	treeShader->SetUniform("scale", TransformSettings::ComputedScaleX, TransformSettings::ComputedScaleY);
	treeShader->SetUniform("pan", TransformSettings::ComputedPanX, TransformSettings::ComputedPanY);
	treeShader->SetUniform("leavesColor", LeavesColor[0], LeavesColor[1], LeavesColor[2]);
	treeShader->SetUniform("trunkColor", TrunkColor[0], TrunkColor[1], TrunkColor[2]);
	treeShader->SetUniform("mergeBranches", FractalSettings::MergeBranches);
	treeShader->SetUniform("maxOrder", FractalSettings::TreeOrder);
	treeShader->Execute();
}

void PythagorasTree::Draw()
{
	simDrawer->Draw(texture.get());
}
