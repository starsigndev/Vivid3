#pragma once
#include <vector>
#include "data.h"

class NodeEntity;
class MeshBuffer;
class MaterialBase;
class NodeCamera;
class NodeLight;

class Mesh3D
{
public:

	Mesh3D();
	void AddVertex(Vertex vertex,bool reset);
	void AddTri(Triangle tri);
	std::vector<Vertex> GetVertices();
	std::vector<Triangle> GetTris();
	void Build();
	MaterialBase* GetMaterial() {
		return m_Material;
	}
	void SetMaterial(MaterialBase* material) {
		m_Material = material;
	}
	void SetOwner(NodeEntity* entity);
	NodeEntity* GetOwner();
	void Render();

private:

	std::vector<Vertex> m_Vertices;
	std::vector<Triangle> m_Tris;
	//
	MeshBuffer* m_Buffer;
	MaterialBase* m_Material;
	NodeEntity* m_Owner;
};

