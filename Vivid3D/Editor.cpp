#include "Editor.h"
#include "SceneGraph.h"
#include "NodeEntity.h"
SceneGraph* Editor::m_Graph = nullptr;

GizmoMode Editor::m_GizmoMode = GM_Translate;
SpaceMode Editor::m_SpaceMode = SM_Global;

NodeEntity* Editor::m_CurrentNode = nullptr;