#include "pch.h"
#include "Engine.h"
#include "RenderTargetCube.h"

RefCntAutoPtr<IRenderDevice>  Engine::m_pDevice;
RefCntAutoPtr<IDeviceContext> Engine::m_pImmediateContext;
RefCntAutoPtr<ISwapChain>     Engine::m_pSwapChain;
RefCntAutoPtr<IShaderSourceInputStreamFactory> Engine::m_pShaderFactory;
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

NodeLight* Engine::m_Light = nullptr;