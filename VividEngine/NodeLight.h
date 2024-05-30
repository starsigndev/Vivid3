#pragma once
#include "Node.h"
class NodeLight :
    public Node
{
public:

    NodeLight();
    float3 GetDiffuse();
    float3 GetSpecular();
    float GetRange();

private:

    float3 m_Diffuse;
    float3 m_Specular;
    float m_Range = 100.0f;



};

