#pragma once

enum GizmoMode {
	GM_Translate,GM_Rotate,GM_Scale
};
enum SpaceMode {
	SM_Local,SM_Global
};

class SceneGraph;
class NodeEntity;
class VSceneGraph;
class VContentBrowser;
class VPropertyEditor;
class Node;

class Editor
{
public:

	static SceneGraph* m_Graph;
	static GizmoMode m_GizmoMode;
	static Node* m_CurrentNode;
	static SpaceMode m_SpaceMode;
	static VSceneGraph* m_SceneGraph;
	static VContentBrowser* m_ContentBrowser;
	static VPropertyEditor* m_PropEditor;
};

