#include "pch.h"
#include "NodeLight.h"
#include "RenderTargetCube.h"

NodeLight::NodeLight() {

	m_Diffuse = float3(1, 1, 1);
	m_Specular = float3(1, 1, 1);
	m_Range = 40.0f;
	m_ShadowMap = new RenderTargetCube(2048,2048);
	m_Name = "Light";
}

float3 NodeLight::GetDiffuse()
{

	return m_Diffuse;

}

float3 NodeLight::GetSpecular() {

	return m_Specular;

}

float NodeLight::GetRange() {

	return m_Range;

}