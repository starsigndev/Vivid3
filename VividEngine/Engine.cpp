#include "pch.h"
#include "Engine.h"

RefCntAutoPtr<IRenderDevice>  Engine::m_pDevice;
RefCntAutoPtr<IDeviceContext> Engine::m_pImmediateContext;
RefCntAutoPtr<ISwapChain>     Engine::m_pSwapChain;
RefCntAutoPtr<IShaderSourceInputStreamFactory> Engine::m_pShaderFactory;
