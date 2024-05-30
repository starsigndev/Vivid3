#include "pch.h"
#include "Engine.h"

RefCntAutoPtr<IRenderDevice>  Engine::m_pDevice;
RefCntAutoPtr<IDeviceContext> Engine::m_pImmediateContext;
RefCntAutoPtr<ISwapChain>     Engine::m_pSwapChain;
RefCntAutoPtr<IShaderSourceInputStreamFactory> Engine::m_pShaderFactory;
NodeCamera* Engine::m_Camera = nullptr;
Node* Engine::m_Node = nullptr;
std::vector<NodeLight*> Engine::m_Lights;

int Engine::GetFrameWidth() {

	return m_FrameWidth;

}

int Engine::GetFrameHeight() {

	return m_FrameHeight;

}

int Engine::m_FrameWidth = 0;
int Engine::m_FrameHeight = 0;