#include "Editor.h"
#include "SceneGraph.h"
#include "NodeEntity.h"
#include "VSceneGraph.h"

SceneGraph* Editor::m_Graph = nullptr;

GizmoMode Editor::m_GizmoMode = GM_Translate;
SpaceMode Editor::m_SpaceMode = SM_Local;

Node* Editor::m_CurrentNode = nullptr;
VSceneGraph* Editor::m_SceneGraph = nullptr;
VContentBrowser* Editor::m_ContentBrowser = nullptr;
VPropertyEditor* Editor::m_PropEditor = nullptr;