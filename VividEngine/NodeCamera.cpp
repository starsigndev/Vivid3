#include "pch.h"
#include "NodeCamera.h"
#include "Engine.h"

float4x4 NodeCamera::GetProjection() {


	float FOVRadians = m_FOV * (3.14159265358979323846f / 180.0f);
	return float4x4::Projection(FOVRadians, (float)Engine::GetFrameWidth() / (float)Engine::GetFrameHeight(), m_NearZ, m_FarZ, true);

}

float4x4 NodeCamera::GetProjection2D() {

	return float4x4::OrthoOffCenter(0, Engine::GetFrameWidth(), Engine::GetFrameHeight(), 0, 0.01f, 10.0f,false);// Projection(FOVRadians, (float)Engine::GetFrameWidth() / (float)Engine::GetFrameHeight(), m_NearZ, m_FarZ, true);


}

float4x4 NodeCamera::GetWorldMatrix() {

	return Node::GetWorldMatrix().Inverse();

}

bool NodeCamera::InView(float3 centre, float3 size) {
    float4x4 viewProjMatrix = GetWorldMatrix() * GetProjection();
    float4x4 vpMatrix = viewProjMatrix;
    // Frustum planes from view-projection matrix
    float4 planes[6];

    // Left
    planes[0] = { vpMatrix._14 + vpMatrix._11, vpMatrix._24 + vpMatrix._21, vpMatrix._34 + vpMatrix._31, vpMatrix._44 + vpMatrix._41 };
    // Right
    planes[1] = { vpMatrix._14 - vpMatrix._11, vpMatrix._24 - vpMatrix._21, vpMatrix._34 - vpMatrix._31, vpMatrix._44 - vpMatrix._41 };
    // Bottom
    planes[2] = { vpMatrix._14 + vpMatrix._12, vpMatrix._24 + vpMatrix._22, vpMatrix._34 + vpMatrix._32, vpMatrix._44 + vpMatrix._42 };
    // Top
    planes[3] = { vpMatrix._14 - vpMatrix._12, vpMatrix._24 - vpMatrix._22, vpMatrix._34 - vpMatrix._32, vpMatrix._44 - vpMatrix._42 };
    // Near
    planes[4] = { vpMatrix._13, vpMatrix._23, vpMatrix._33, vpMatrix._43 };
    // Far
    planes[5] = { vpMatrix._14 - vpMatrix._13, vpMatrix._24 - vpMatrix._23, vpMatrix._34 - vpMatrix._33, vpMatrix._44 - vpMatrix._43 };

    // Normalize the planes
    for (int i = 0; i < 6; ++i) {
        float length = sqrtf(planes[i].x * planes[i].x + planes[i].y * planes[i].y + planes[i].z * planes[i].z);
        planes[i] /= length;
    }

    // Check each plane
    float3 halfSize = size / 2.0f;
    float3 corners[8] = {
        { centre.x - halfSize.x, centre.y - halfSize.y, centre.z - halfSize.z },
        { centre.x + halfSize.x, centre.y - halfSize.y, centre.z - halfSize.z },
        { centre.x - halfSize.x, centre.y + halfSize.y, centre.z - halfSize.z },
        { centre.x + halfSize.x, centre.y + halfSize.y, centre.z - halfSize.z },
        { centre.x - halfSize.x, centre.y - halfSize.y, centre.z + halfSize.z },
        { centre.x + halfSize.x, centre.y - halfSize.y, centre.z + halfSize.z },
        { centre.x - halfSize.x, centre.y + halfSize.y, centre.z + halfSize.z },
        { centre.x + halfSize.x, centre.y + halfSize.y, centre.z + halfSize.z }
    };

    for (int i = 0; i < 6; ++i) {
        bool outside = true;
        for (const auto& corner : corners) {
            float distance = planes[i].x * corner.x + planes[i].y * corner.y + planes[i].z * corner.z + planes[i].w;
            if (distance >= 0) {
                outside = false;
                break;
            }
        }
        if (outside) {
            return false;
        }
    }

    return true;
}