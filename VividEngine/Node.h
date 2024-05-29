#pragma once
#include <vector>
#include <string>
#include "BasicMath.hpp"

using namespace Diligent;

class Node
{
public:

	Node();

	//transform

	//hierarchy
	void AddNode(Node* node);
	int NodesCount();
	Node* GetNode(int index);
	std::vector<Node*> GetNodes();
	virtual float4x4 GetWorldMatrix();


private:

	//transform
	float4x4 m_Rotation;
	float3 m_Position;
	float3 m_Scale;

	//hierarchy. 
	Node* m_Root;
	std::vector<Node*> m_Nodes;

};

