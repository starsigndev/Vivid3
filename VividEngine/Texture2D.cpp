#include "pch.h"
#include "Texture2D.h"
#include <thread>


void _load_texture(Texture2D* texture)
{

    auto tex = new Texture2D(texture->GetPath(), false);
    texture->Set(tex->GetTex(),tex->GetView());
    texture->Loaded();
    delete tex;
}

Texture2D* Texture2D::WhiteTex = nullptr;

Texture2D::Texture2D(std::string path,bool threaded) {

    int b = 5;

    if (!threaded) {
        TextureLoadInfo loadInfo;

        CreateTextureFromFile(path.c_str(), loadInfo, Engine::m_pDevice, &m_pTexture);

        m_pTextureView = m_pTexture->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

        m_Path = path;
        m_Loading = false;

    }
    else {

        m_Path = path;
        m_Loading = true;
        load = std::thread(_load_texture, this);

    }
}

Texture2D::Texture2D(int w, int h, float* data, int bpp)
{
    m_Width = w;
    m_Height = h;
    
    TextureDesc TexDesc;
    TexDesc.Name = "Float Tex2D"; // Name of the texture
    TexDesc.Type = RESOURCE_DIM_TEX_2D; // Cube map type
    TexDesc.Width = w;
    TexDesc.Height = h;
    TexDesc.Format = TEX_FORMAT_RGBA32_FLOAT; ;// Engine::m_pSwapChain->GetCurrentBackBufferRTV()->GetDesc().Format;  //DXGI_FORMAT_R32G32B32A32_FLOAT; // Assuming RGBA EXR format
    TexDesc.BindFlags = BIND_SHADER_RESOURCE;
    TexDesc.Usage = USAGE_IMMUTABLE;
   
    TexDesc.MipLevels = 1;
    std::vector<TextureSubResData> res;

    TextureSubResData adata;
    adata.pData = data;
    adata.Stride = w * sizeof(float) * 4;

    TextureData tdata;
    tdata.NumSubresources = 1;
    tdata.pSubResources = &adata;


    RefCntAutoPtr<ITexture> pTexture;
    Engine::m_pDevice->CreateTexture(TexDesc, &tdata, &pTexture);
    m_pTexture = pTexture;
    m_pTextureView = pTexture->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

}