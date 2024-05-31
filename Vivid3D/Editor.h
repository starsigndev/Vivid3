#pragma once

enum GizmoMode {
	GM_Translate,GM_Rotate,GM_Scale
};
enum SpaceMode {
	SM_Local,SM_Global
};

class SceneGraph;
class NodeEntity;

class Editor
{
public:

	static SceneGraph* m_Graph;
	static GizmoMode m_GizmoMode;
	static NodeEntity* m_CurrentNode;
	static SpaceMode m_SpaceMode;

};

