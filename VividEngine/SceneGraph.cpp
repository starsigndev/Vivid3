#include "pch.h"
#include "SceneGraph.h"
#include "Node.h"
#include "NodeEntity.h"
#include "NodeCamera.h"
#include "Engine.h"

SceneGraph::SceneGraph() {

	m_Camera = new NodeCamera;
	m_RootNode = new Node();
	
}

void SceneGraph::AddNode(Node* node) {

	m_RootNode->AddNode(node);

}

void SceneGraph::AddLight(NodeLight* light) {

	m_Lights.push_back(light);

}

void SceneGraph::Render() {

	Engine::m_Camera = m_Camera;
	Engine::m_Lights = m_Lights;
	m_RootNode->Render();
	

}

NodeCamera* SceneGraph::GetCamera() {

	return m_Camera;

}