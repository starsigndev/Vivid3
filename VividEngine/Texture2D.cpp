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