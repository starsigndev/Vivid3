#include "pch.h"
#include "SceneGraph.h"
#include "Node.h"
#include "NodeEntity.h"
#include "NodeCamera.h"

SceneGraph::SceneGraph() {

	m_Camera = new NodeCamera;
	
}

void SceneGraph::AddNode(Node* node) {

	m_RootNode->AddNode(node);

}

void SceneGraph::Render() {



}