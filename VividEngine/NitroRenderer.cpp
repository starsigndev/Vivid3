#include "pch.h"
#include "NitroRenderer.h"
#include "SceneGraph.h"

void NitroRenderer::PreRender()
{

	GetSceneGraph()->RenderShadows();

}

void NitroRenderer::Render(bool no_render) {

	GetSceneGraph()->Render();

}