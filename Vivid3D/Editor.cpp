#include "Editor.h"
#include "SceneGraph.h"
#include "NodeEntity.h"
#include "VSceneGraph.h"
#include "Engine.h"

SceneGraph* Editor::m_Graph = nullptr;

GizmoMode Editor::m_GizmoMode = GM_Translate;
SpaceMode Editor::m_SpaceMode = SM_Local;
RunMode Editor::m_RunMode = RM_Stopped;

Node* Editor::m_CurrentNode = nullptr;
VSceneGraph* Editor::m_SceneGraph = nullptr;
VContentBrowser* Editor::m_ContentBrowser = nullptr;
VPropertyEditor* Editor::m_PropEditor = nullptr;


void Editor::BeginPlay() {
	if (m_RunMode == RM_Playing) return;
	m_RunMode = RM_Playing;
//	m_SceneGraph->BeginPlay();
	Engine::m_ActiveGraph->BeginPlay();
}

void Editor::Stop() {
	if (m_RunMode == RM_Stopped) return;
	m_RunMode = RM_Stopped;
	Engine::m_ActiveGraph->Stop();
}