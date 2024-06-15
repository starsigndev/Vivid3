#pragma once
#include <vector>
#include "data.h"

class NodeEntity;
class MeshBuffer;
class MaterialBase;
class NodeCamera;
class NodeLight;
class MaterialDepth;

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
	MaterialDepth* GetDepthMaterial()
	{
		return m_DepthMaterial;
	}

	void SetDepthMaterial(MaterialDepth* depth)
	{
		m_DepthMaterial = depth;
	}
	void SetOwner(NodeEntity* entity);
	NodeEntity* GetOwner();
	void Render(bool sp);
	void RenderDepth();
	void BuildGeo();
	std::vector<float3> GetGeo() {
		return m_Build;
	}
	void NeedsRebuild() {
		n_NeedsRebuild = true;
	}
	bool RebuildIf() {
		return n_NeedsRebuild;
	}
	
private:

	std::vector<Vertex> m_Vertices;
	std::vector<Triangle> m_Tris;
	//
	MeshBuffer* m_Buffer;
	MaterialBase* m_Material;
	MaterialDepth* m_DepthMaterial;
	NodeEntity* m_Owner;
	std::vector<float3> m_Build;
	bool n_NeedsRebuild = true;
};

