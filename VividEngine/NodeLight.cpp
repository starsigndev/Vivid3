#include "pch.h"
#include "NodeLight.h"

NodeLight::NodeLight() {

	m_Diffuse = float3(1, 1, 1);
	m_Specular = float3(1, 1, 1);
	m_Range = 12.0f;

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