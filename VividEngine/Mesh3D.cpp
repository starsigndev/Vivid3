#include "pch.h"
#include "Mesh3D.h"
#include "MeshBuffer.h"
#include "Engine.h"
#include "MaterialBase.h"
#include "MaterialMeshLight.h"
#include "MaterialDepth.h"
#include "NodeEntity.h"
Mesh3D::Mesh3D() {
	//m_Material = new MaterialBase;

}

void Mesh3D::AddVertex(Vertex vertex,bool reset) {


	if (reset) {
		//vertex.bone_ids = float4(-1, -1, -1, -1);
		//vertex.bone_weights = float4(0, 0, 0, 0);
		vertex.bone_ids = float4(-1, -1, -1, -1);
		vertex.bone_weights = float4(0, 0, 0, 0);
	}
	m_Vertices.push_back(vertex);
}

void Mesh3D::AddTri(Triangle tri) {

	m_Tris.push_back(tri);

}

std::vector<Vertex> Mesh3D::GetVertices() {

	return m_Vertices;

}

std::vector<Triangle> Mesh3D::GetTris() {

	return m_Tris;

}

void Mesh3D::Build() {

	m_Buffer = new MeshBuffer;
	m_Buffer->SetMesh(this);
	m_Buffer->Build();

}

void Mesh3D::Render(bool sp) {

	

	Uint64 offsets = 0;

	
	IBuffer* pBuffs[] = { m_Buffer->GetVertexBuffer() };

	Engine::m_pImmediateContext->SetVertexBuffers(0, 1, pBuffs, &offsets, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
	Engine::m_pImmediateContext->SetIndexBuffer(m_Buffer->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	if (sp) {
		Engine::m_pImmediateContext->CommitShaderResources(m_Material->GetSecondPassSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}
	else {
		Engine::m_pImmediateContext->CommitShaderResources(m_Material->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}
	DrawIndexedAttribs attrib;
	attrib.IndexType = VALUE_TYPE::VT_UINT32;
	attrib.NumIndices = m_Tris.size() * 3;
	attrib.Flags = DRAW_FLAG_VERIFY_ALL;
	Engine::m_pImmediateContext->DrawIndexed(attrib);

}

void Mesh3D::RenderDepth() {

	Uint64 offsets = 0;


	IBuffer* pBuffs[] = { m_Buffer->GetVertexBuffer() };

	Engine::m_pImmediateContext->SetVertexBuffers(0, 1, pBuffs, &offsets, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
	Engine::m_pImmediateContext->SetIndexBuffer(m_Buffer->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	Engine::m_pImmediateContext->CommitShaderResources(m_DepthMaterial->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	DrawIndexedAttribs attrib;
	attrib.IndexType = VALUE_TYPE::VT_UINT32;
	attrib.NumIndices = m_Tris.size() * 3;
	attrib.Flags = DRAW_FLAG_VERIFY_ALL;
	Engine::m_pImmediateContext->DrawIndexed(attrib);

}

void Mesh3D::SetOwner(NodeEntity* entity) {

	m_Owner = entity;

}

NodeEntity* Mesh3D::GetOwner() {

	return m_Owner;

}

void Mesh3D::BuildGeo() {

	if (n_NeedsRebuild == false) return;
	//printf("REBUILDING GEO: Tris:%d\n",GetTris().size());
	auto world = m_Owner->GetWorldMatrix();

	auto tris = GetTris();
	auto verts = GetVertices();
	m_Build.clear();

	for (auto t : tris) {

		float3 v0 = verts[t.v0].position * world;
		float3 v1 = verts[t.v1].position * world;
		float3 v2 = verts[t.v2].position * world;
		m_Build.push_back(v0);
		m_Build.push_back(v1);
		m_Build.push_back(v2);


	}

	n_NeedsRebuild = false;

}
