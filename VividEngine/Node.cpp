#include "pch.h"
#include "Node.h"

Node::Node() {

	m_Rotation = float4x4::Identity();
	m_Position = float3(0, 0, 0);
	m_Scale = float3(1, 1, 1);

}

void Node::AddNode(Node* node) {

	m_Nodes.push_back(node);

}

int Node::NodesCount() {

	return m_Nodes.size();

}

Node* Node::GetNode(int index) {

	return m_Nodes[index];

}

std::vector<Node*> Node::GetNodes()
{

	return m_Nodes;

}

float4x4 Node::GetWorldMatrix() {

	float4x4 translationMatrix = float4x4::Translation(m_Position);
	float4x4 rotationMatrix = m_Rotation;
	float4x4 scaleMatrix = float4x4::Scale(m_Scale);

	// Combine the transformation matrices in the correct order (scale * rotation * translation)
	float4x4 worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	return worldMatrix;

}