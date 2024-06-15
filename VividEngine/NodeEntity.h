#pragma once
#include <vector>
#include "Node.h"


class MaterialBase;
class Mesh3D;

class NodeEntity : public Node
{
public:

	NodeEntity();
	void AddMesh(Mesh3D* mesh);
	int MeshesCount();
	Mesh3D* GetMesh(int index);
	std::vector<Mesh3D*> GetMeshes();
	void Render();
	void RenderDepth();
	void SetMaterial(MaterialBase* material);
	bool IsMeshIndex(Mesh3D* mesh, int index);
	void BuildGeo();

private:

	std::vector<Mesh3D*> m_Meshes;



};

