#pragma once

enum GizmoMode {
	GM_Translate,GM_Rotate,GM_Scale
};
enum SpaceMode {
	SM_Local,SM_Global
};

enum RunMode {
	RM_Playing,RM_Stopped,RM_Paused,
};

enum TerrainEditMode {
	EM_Paint,EM_Sculpt
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
	static RunMode m_RunMode;
	static SceneGraph* m_Graph;
	static GizmoMode m_GizmoMode;
	static Node* m_CurrentNode;
	static SpaceMode m_SpaceMode;
	static TerrainEditMode m_TerrainEditMode;
	static VSceneGraph* m_SceneGraph;
	static VContentBrowser* m_ContentBrowser;
	static VPropertyEditor* m_PropEditor;
	static void BeginPlay();
	static void Stop();
	static float TerrainX;
	static float TerrainZ;
	static float TerrainBrushSize;
	static float TerrainBrushStrength;
	static int TerrainEditLayer;

};
