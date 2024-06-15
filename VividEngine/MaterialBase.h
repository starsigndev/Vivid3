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
	virtual void Bind(bool sp);
	RefCntAutoPtr<IShaderResourceBinding> GetSRB() {
		return m_SRB;
	}
	RefCntAutoPtr<IShaderResourceBinding> GetSecondPassSRB() {
		return m_SecondPassSRB;
	}
	void SetDiffuse(Texture2D* texture);
	void SetSpecular(Texture2D* texture);
	void SetNormals(Texture2D* texture);
	Texture2D* GetDiffuse() {
		return m_Diffuse;
	}
	Texture2D* GetSpecular() {
		return m_Specular;
	}
	Texture2D* GetNormal() {
		return m_Normal;
	}
	virtual void SaveMaterial(std::string path);
	virtual void LoadMaterial(std::string path);
	std::string GetPath() {
		return m_FullPath;
	}
	float4 GetDiffuseColor() {
		return m_DiffuseColor;
	}
	float4 GetSpecularColor() {
		return m_SpecularColor;
	}
	void SetDiffuseColor(float4 diff) {
		m_DiffuseColor = diff;
	}
	void SetSpecularColor(float4 spec) {
		m_SpecularColor = spec;
	}

protected:

	//Textures
	Texture2D* m_Diffuse;
	Texture2D* m_Normal;
	Texture2D* m_Specular;

	float4 m_DiffuseColor;
	float4 m_SpecularColor;

	bool m_CastShadows = true;
	bool m_ReceiveShadows = true;

	//Basic
	RefCntAutoPtr<IBuffer> BasicUniform;
	RefCntAutoPtr<IBuffer> BasicUniform2;
	//
	RefCntAutoPtr<IShader> m_VS;
	RefCntAutoPtr<IShader> m_PS;
	RefCntAutoPtr<IPipelineState> m_Pipeline;
	RefCntAutoPtr<IPipelineState> m_SecondPassPipeline;
	RefCntAutoPtr<IBuffer> m_UniformBuffer;
	RefCntAutoPtr<IShaderResourceBinding> m_SRB;
	RefCntAutoPtr<IShaderResourceBinding> m_SecondPassSRB;
	std::string m_FullPath;

};

