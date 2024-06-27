#include "pch.h"
#include "RenderTarget2D.h"
#include "Engine.h"

RenderTarget2D::RenderTarget2D(int width, int height) {

	m_Width = width;
	m_Height = height;

	TextureDesc desc;
	desc.Name = "RenderTarget2D Texture";
	desc.Type = RESOURCE_DIM_TEX_2D;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.Format = TEX_FORMAT_RGBA32_FLOAT;
	desc.BindFlags = BIND_FLAGS::BIND_SHADER_RESOURCE | BIND_FLAGS::BIND_RENDER_TARGET;
	desc.ClearValue.Format = desc.Format;
	desc.ClearValue.Color[0] = 0;
	desc.ClearValue.Color[1] = 0;
	desc.ClearValue.Color[2] = 0;
	desc.ClearValue.Color[3] = 1;
	desc.SampleCount = 1;

	Engine::m_pDevice->CreateTexture(desc, nullptr, &m_Texture);
	m_RTView = m_Texture->GetDefaultView(TEXTURE_VIEW_RENDER_TARGET);
	m_ShaderView = m_Texture->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

	TextureDesc depth = desc;
	depth.Name = "RenderTarget2D Depth Texture";
	depth.Format = TEX_FORMAT_D32_FLOAT;
	depth.BindFlags = BIND_FLAGS::BIND_DEPTH_STENCIL;
	depth.ClearValue.Format = depth.Format;
	depth.ClearValue.DepthStencil.Depth = 1.0;
	depth.ClearValue.DepthStencil.Stencil = 0;

	Engine::m_pDevice->CreateTexture(depth, nullptr, &m_DepthTexture);
	m_DepthView = m_DepthTexture->GetDefaultView(TEXTURE_VIEW_DEPTH_STENCIL);



	

}

void RenderTarget2D::Bind() {

	//ITextureView* tv = m_DepthTexView;
	float ClearColor[4] = { 0,0,0,1.0 };
	//if (!m_Depth) {
	//	ClearColor[0] = 0;
	//	ClearColor[1] = 0;
	//	ClearColor[2] = 0;
//	}


	Engine::SetBoundRT2D(this);

	Engine::m_pImmediateContext->SetRenderTargets(1, &m_RTView,m_DepthView, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	Engine::m_pImmediateContext->ClearRenderTarget(m_RTView,ClearColor, RESOURCE_STATE_TRANSITION_MODE_VERIFY);
	Engine::m_pImmediateContext->ClearDepthStencil(m_DepthView, CLEAR_DEPTH_FLAG, 1.0f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);



}

void RenderTarget2D::Release() {

	auto pRTV = Engine::m_pSwapChain->GetCurrentBackBufferRTV();

	Engine::m_pImmediateContext->SetRenderTargets(1, &pRTV, Engine::m_pSwapChain->GetDepthBufferDSV(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	Engine::SetBoundRT2D(nullptr);

}