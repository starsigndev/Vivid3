#pragma once
#include "BasicMath.hpp"

using namespace Diligent;
class SceneGraph;
class RenderTargetCube;

class CubeRenderer
{
public:

	CubeRenderer(SceneGraph* graph, RenderTargetCube* target);
	void RenderDepth(float3 position, float maxZ);

private:

	SceneGraph* m_Graph;
	RenderTargetCube* m_Target;


};

