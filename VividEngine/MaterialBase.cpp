#include "pch.h"
#include "MaterialBase.h"
#include "Engine.h"

MaterialBase::MaterialBase() {

    Create();

}

void MaterialBase::Create() {

    SetVertexShader("basic.vsh");
    SetPixelShader("basic.psh");

}

void MaterialBase::SetVertexShader(std::string path) {

    const char* filePath = path.c_str();

    // Allocate memory for the Diligent::Char* and copy the string
    size_t length = path.length();
    Char* diligentPath = new Char[length + 1]; // +1 for null terminator
    std::strcpy(diligentPath, filePath);

    ShaderDesc desc;

    desc.Name = diligentPath;
    desc.ShaderType = SHADER_TYPE_VERTEX;
    desc.UseCombinedTextureSamplers = true;
          

	ShaderCreateInfo info;
    info.FilePath = diligentPath;
    info.pShaderSourceStreamFactory = Engine::m_pShaderFactory;
    info.Desc = desc;
    info.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

	Engine::m_pDevice->CreateShader(info, &m_VS);


}

void MaterialBase::SetPixelShader(std::string path) {

    const char* filePath = path.c_str();

    // Allocate memory for the Diligent::Char* and copy the string
    size_t length = path.length();
    Char* diligentPath = new Char[length + 1]; // +1 for null terminator
    std::strcpy(diligentPath, filePath);

    ShaderDesc desc;

    desc.Name = diligentPath;
    desc.ShaderType = SHADER_TYPE_PIXEL;
    desc.UseCombinedTextureSamplers = true;

    ShaderCreateInfo info;
    info.FilePath = diligentPath;
    info.pShaderSourceStreamFactory = Engine::m_pShaderFactory;
    info.Desc = desc;
    info.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

    Engine::m_pDevice->CreateShader(info, &m_PS);

}