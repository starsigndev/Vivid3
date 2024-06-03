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

	//Transform
	void SetPosition(float3 position);
	void SetRotation(float pitch, float yaw, float roll);
	float3 GetPosition();
	void Move(float3 delta);
	void Translate(float3 delta);
	void Rotate(float pitch, float yaw, float roll);
	void Turn(float pitch, float yaw, float roll, bool local);
	float4x4 GetRotation() {
		return m_Rotation;
	}
	void SetRotation(float4x4 rotation) {
		m_Rotation = rotation;
	}
	float3 TransformVector(float3 vector);
	virtual float4x4 GetWorldMatrix();
	virtual void Render() {
		RenderChildren();
	};
	virtual void RenderDepth() {
		RenderDepthChildren();
	}
	void RenderDepthChildren() {
		for (auto node : m_Nodes) {
			node->RenderDepth();
		}
	}
	void RenderChildren() {
		for (auto node : m_Nodes) {
			node->Render();
		}
	}
	std::string GetName() {
		return m_Name;
	}
	void SetName(std::string name) {
		m_Name = name;
	}


private:

	std::string m_Name;

	//transform
	float4x4 m_Rotation;
	float3 m_Position;
	float3 m_Scale;

	//hierarchy. 
	Node* m_Root;
	std::vector<Node*> m_Nodes;

};

