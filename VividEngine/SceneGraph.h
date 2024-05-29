#pragma once
#include <vector>
#include <string>

class Node;
class NodeEntity;
class NodeCamera;

class SceneGraph
{
public:

	SceneGraph();

	void AddNode(Node* node);
	void Render();

private:

	NodeCamera* m_Camera;
	Node* m_RootNode = nullptr;

};

