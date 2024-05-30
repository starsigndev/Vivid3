#include "pch.h"
#include "Texture2D.h"


Texture2D::Texture2D(std::string path) {

    TextureLoadInfo loadInfo;

    CreateTextureFromFile(path.c_str(), loadInfo,Engine::m_pDevice , &m_pTexture);
    
    m_pTextureView =  m_pTexture->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);


}