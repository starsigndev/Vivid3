#pragma once
#include <vector>
#include <string>
#include "BasicMath.hpp"

using namespace Diligent;

class Intersections;
class Node;
class NodeEntity;
class NodeCamera;
class NodeLight;
class Mesh3D;
class CubeRenderer;
class MeshLines;
class Bounds;
class NodeTerrain;


struct SceneInfo {

	bool m_Empty = false;
	int m_TriCount = 0;
	int m_VertCount = 0;
	std::vector<Node*> m_Nodes;
	std::vector<Mesh3D*> m_Meshes;
	std::vector<Mesh3D*> m_LocalMeshes;

};

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
	void RenderShadows();
	void Render();
	Node* FindNode(std::string url);
	void RenderDepth();
	NodeCamera* GetCamera();
	void SetCamera(NodeCamera* camera) {
		m_Camera = camera;
	}
	Node* GetRoot() {
		return m_RootNode;
	}
	void AddLines(MeshLines* line);
	HitResult MousePick(int x, int y);
	HitResult MousePick(int x, int y, NodeEntity* entity);
	HitResult MousePick(int x, int y, NodeTerrain* terrain);
	HitResult RayCast(float3 pos, float3 dir);
	float2 ToScreenSpace(float3 position);
	std::vector<NodeLight*> GetLights() {
		return m_Lights;
	}
	void Update();
	void BeginPlay();
	void Stop();
	SceneInfo GetInfo(float3 centre, float3 size, bool include_local = false);

	Bounds GetBounds();

private:

	NodeCamera* m_Camera;
	Node* m_RootNode = nullptr;
	std::vector<NodeLight*> m_Lights;
	CubeRenderer* m_CubeRenderer;
	bool m_IsPlaying = false;
	std::vector<MeshLines*> m_Lines;
	Intersections* m_RayTester;
};

