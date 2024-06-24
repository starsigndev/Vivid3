#include "Editor.h"
#include "SceneGraph.h"
#include "NodeEntity.h"
#include "VSceneGraph.h"
#include "Engine.h"
#include "Vivid3D.h"
#include <qboxlayout.h>

SceneGraph* Editor::m_Graph = nullptr;

GizmoMode Editor::m_GizmoMode = GM_Translate;
SpaceMode Editor::m_SpaceMode = SM_Local;
RunMode Editor::m_RunMode = RM_Stopped;
TerrainEditMode Editor::m_TerrainEditMode = EM_Paint;

Node* Editor::m_CurrentNode = nullptr;
VSceneGraph* Editor::m_SceneGraph = nullptr;
VContentBrowser* Editor::m_ContentBrowser = nullptr;
VPropertyEditor* Editor::m_PropEditor = nullptr;
Vivid3D* Editor::m_Main = nullptr;
VTrackFrame* Editor::m_TrackPanel = nullptr;



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

float Editor::TerrainX = 0;
float Editor::TerrainZ = 0;
float Editor::TerrainBrushSize = 5.5f;
float Editor::TerrainBrushStrength = 0.55f;
int Editor::TerrainEditLayer = 0;