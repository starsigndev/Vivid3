#include "pch.h"
#include "Engine.h"
#include "RenderTargetCube.h"
#include "MaterialBase.h"
#include "ScriptHost.h"

RefCntAutoPtr<IRenderDevice>  Engine::m_pDevice;
RefCntAutoPtr<IDeviceContext> Engine::m_pImmediateContext;
RefCntAutoPtr<ISwapChain>     Engine::m_pSwapChain;
RefCntAutoPtr<IShaderSourceInputStreamFactory> Engine::m_pShaderFactory;

ScriptHost* Engine::m_ScriptHost = nullptr;

NodeCamera* Engine::m_Camera = nullptr;
Node* Engine::m_Node = nullptr;
std::vector<NodeLight*> Engine::m_Lights;
RenderTargetCube* Engine::m_BoundRTC = nullptr;

int Engine::GetFrameWidth() {

	if (m_BoundRTC != nullptr) {
		return m_BoundRTC->GetWidth();
	}
	return m_FrameWidth;

}

int Engine::GetFrameHeight() {

	if (m_BoundRTC != nullptr) {
		return m_BoundRTC->GetHeight();
	}
	return m_FrameHeight;


}

void Engine::SetFrameWidth(int w) {

	m_FrameWidth = w;

}

void Engine::SetFrameHeight(int h) {

	m_FrameHeight = h;

}

int Engine::m_FrameWidth = 0;
int Engine::m_FrameHeight = 0;

void Engine::ClearZ() {

	m_pImmediateContext->ClearDepthStencil(m_pSwapChain->GetDepthBufferDSV(), CLEAR_DEPTH_FLAG, 1.0f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


}

void Engine::SetBoundRTC(RenderTargetCube* target) {

	m_BoundRTC = target;

}

bool containsSubstring(const std::string& str, const std::string& substring) {
	return str.find(substring) != std::string::npos;
}

MaterialBase* Engine::FindActiveMaterial(std::string path) {

	for (auto mat : m_ActiveMaterials) {

		if (mat->GetPath() == path) {
			return mat;
		}
		if (containsSubstring(mat->GetPath(), path))
		{
			return mat;
		}
		if (mat->GetPath().length() > 0) {
			if (containsSubstring(path, mat->GetPath()))
			{
				return mat;
			}
		}

	}
	return nullptr;

}

std::vector<MaterialBase*> Engine::m_ActiveMaterials;

NodeLight* Engine::m_Light = nullptr;

SceneGraph* Engine::m_ActiveGraph = nullptr;