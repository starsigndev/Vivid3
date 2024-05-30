#include "pch.h"
#include "NodeCamera.h"
#include "Engine.h"

float4x4 NodeCamera::GetProjection() {


	float FOVRadians = m_FOV * (3.14159265358979323846f / 180.0f);
	return float4x4::Projection(FOVRadians, (float)Engine::GetFrameWidth() / (float)Engine::GetFrameHeight(), m_NearZ, m_FarZ, true);

}

float4x4 NodeCamera::GetWorldMatrix() {

	return Node::GetWorldMatrix().Inverse();

}