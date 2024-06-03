#pragma once
#include "Node.h"

class RenderTargetCube;

class NodeLight :
    public Node
{
public:

    NodeLight();
    float3 GetDiffuse();
    float3 GetSpecular();
    float GetRange();
    RenderTargetCube* GetShadowMap() {
        return m_ShadowMap;
    }

private:

    float3 m_Diffuse;
    float3 m_Specular;
    float m_Range = 100.0f;
    RenderTargetCube* m_ShadowMap;


};

