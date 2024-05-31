#pragma once
#include <vector>
#include <string>
#include "BasicMath.hpp"
using namespace Diligent;

class Node;
class NodeEntity;
class NodeCamera;
class NodeLight;
class Mesh3D;

struct HitResult {

	bool m_Hit = false;
	Node* m_Node = nullptr;
	float3 m_Point;
	float m_Distance = 10000.0f;
	Mesh3D* m_Mesh;
	NodeEntity* m_Entity = nullptr;

};

class SceneGraph
{
public:

	SceneGraph();

	void AddNode(Node* node);
	void AddLight(NodeLight* light);
	void Render();
	NodeCamera* GetCamera();
	Node* GetRoot() {
		return m_RootNode;
	}

	HitResult MousePick(int x, int y);
	HitResult MousePick(int x, int y, NodeEntity* entity);
	HitResult RayCast(float3 pos, float3 dir);
	
private:

	NodeCamera* m_Camera;
	Node* m_RootNode = nullptr;
	std::vector<NodeLight*> m_Lights;

};

