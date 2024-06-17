#pragma once
#include <string>

//#include <Graphics/GraphicsEngine/interface/GraphicsEngine.h>
#include <Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <Graphics/GraphicsEngine/interface/Texture.h>
#include <Graphics/GraphicsEngine/interface/TextureView.h>
#include <Graphics/GraphicsEngine/interface/SwapChain.h>
#include <Common/interface/RefCntAutoPtr.hpp>
//#include <Common/interface/FileStream.h>

#include <TextureUtilities.h>
#include "Engine.h"
#include <thread>
#include <mutex>

using namespace Diligent;



class Texture2D
{
public:

	static Texture2D* WhiteTex;
	Texture2D(std::string path,bool threaded = false);
	RefCntAutoPtr<ITextureView> GetView() {
		if (m_Loading) {
			return WhiteTex->GetView();
		}
		return m_pTextureView;
	}
	RefCntAutoPtr<ITexture> GetTex() {
		if (m_Loading) {
			return WhiteTex->GetTex();
		}
		return m_pTexture;
	}
	void Set(RefCntAutoPtr<ITexture> tex,RefCntAutoPtr<ITextureView> view)
	{
		m_pTextureView = view;
		m_pTexture = tex;

	}
	std::string GetPath() {
		return m_Path;
	}
	void Loaded() {
		m_Loading = false;
	}
private:

	RefCntAutoPtr<ITexture> m_pTexture;
	RefCntAutoPtr<ITextureView> m_pTextureView;
	std::string m_Path;
	bool m_Loading = false;
	std::thread load;
};

