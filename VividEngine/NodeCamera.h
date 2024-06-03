#pragma once
#include "Node.h"
class NodeCamera :
    public Node 
{
public:

    float4x4 GetProjection();
    float4x4 GetWorldMatrix();
    float4x4 GetInverseViewProjectionMatrix() {

        float4x4 viewProjMatrix = GetProjection() * GetWorldMatrix();

        float4x4 invViewProjMatrix = viewProjMatrix.Inverse();

        return invViewProjMatrix;


    }

    float GetNearZ() {
        return m_NearZ;
    }

    float GetFarZ() {
        return m_FarZ;
    }

    void SetNearZ(float z) {
        m_NearZ = z;
    }
    void SetFarZ(float z) {

        m_FarZ = z;
    }
    void SetFov(float fov) {
        m_FOV = fov;
    }

private:

    float m_NearZ = 0.1f;
    float m_FarZ = 30.0f;
    float m_FOV = 45.0f;


};

