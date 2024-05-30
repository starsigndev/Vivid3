#pragma once
#include <vector>
#include <string>

class Node;
class NodeEntity;
class NodeCamera;
class NodeLight;

class SceneGraph
{
public:

	SceneGraph();

	void AddNode(Node* node);
	void AddLight(NodeLight* light);
	void Render();
	NodeCamera* GetCamera();

private:

	NodeCamera* m_Camera;
	Node* m_RootNode = nullptr;
	std::vector<NodeLight*> m_Lights;

};

