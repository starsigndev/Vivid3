#pragma once
#include <vector>
#include "Node.h"


class MaterialBase;
class Mesh3D;

class NodeEntity : Node
{
public:

	NodeEntity();
	void AddMesh(Mesh3D* mesh);
	int MeshesCount();
	Mesh3D* GetMesh(int index);
	std::vector<Mesh3D*> GetMeshes();

private:

	std::vector<Mesh3D*> m_Meshes;
	MaterialBase* m_Material;

};

