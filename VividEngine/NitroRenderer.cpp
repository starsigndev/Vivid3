#include "pch.h"
#include "NitroRenderer.h"
#include "SceneGraph.h"

void NitroRenderer::PreRender()
{

	GetSceneGraph()->RenderShadows();

}

void NitroRenderer::Render() {

	GetSceneGraph()->Render();

}