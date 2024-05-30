#pragma once
#include "Node.h"
class NodeCamera :
    public Node 
{
public:

    float4x4 GetProjection();
    float4x4 GetWorldMatrix();

private:

    float m_NearZ = 0.1f;
    float m_FarZ = 100.0f;
    float m_FOV = 45.0f;


};

