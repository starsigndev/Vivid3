#pragma once
#include <string>

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "BasicMath.hpp"

using namespace Diligent;

class Texture2D;

class MaterialBase
{
public:

	MaterialBase();
	virtual void Create();
	void SetVertexShader(std::string path);
	void SetPixelShader(std::string path);
	RefCntAutoPtr<IBuffer> CreateUniform(int size, std::string name);
	virtual void Bind();
	RefCntAutoPtr<IShaderResourceBinding> GetSRB() {
		return m_SRB;
	}
	void SetDiffuse(Texture2D* texture);
	void SetSpecular(Texture2D* texture);
	void SetNormals(Texture2D* texture);
	virtual void SaveMaterial(std::string path);
	virtual void LoadMaterial(std::string path);

protected:

	//Textures
	Texture2D* m_Diffuse;
	Texture2D* m_Normal;
	Texture2D* m_Specular;

	float4 m_DiffuseColor;
	float4 m_SpecularColor;

	//Basic
	RefCntAutoPtr<IBuffer> BasicUniform;

	//
	RefCntAutoPtr<IShader> m_VS;
	RefCntAutoPtr<IShader> m_PS;
	RefCntAutoPtr<IPipelineState> m_Pipeline;
	RefCntAutoPtr<IPipelineState> m_SecondPassPipeline;
	RefCntAutoPtr<IBuffer> m_UniformBuffer;
	RefCntAutoPtr<IShaderResourceBinding> m_SRB;
	RefCntAutoPtr<IShaderResourceBinding> m_SecondPassSRB;


};

