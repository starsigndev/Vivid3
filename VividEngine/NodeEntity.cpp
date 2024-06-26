#include "pch.h"
#include "NodeEntity.h"
#include "MaterialBase.h"
#include "MaterialDepth.h"
#include <windows.h>
#include "Mesh3D.h"
#include "Engine.h"
#include "Bounds.h"
#include "VFile.h"
#include "Importer.h"

NodeEntity::NodeEntity() {

	m_Static = true;
	

}

void NodeEntity::AddMesh(Mesh3D* mesh) {

	m_Meshes.push_back(mesh);
	mesh->SetOwner(this);

}

int NodeEntity::MeshesCount() {

	return m_Meshes.size();

}

Mesh3D* NodeEntity::GetMesh(int index) {

	return m_Meshes[index];

}

std::vector<Mesh3D*> NodeEntity::GetMeshes() {

	return m_Meshes;

}

void NodeEntity::RenderDepth() {

	Engine::m_Node = this;
	for (auto mesh : m_Meshes) {
	
		if (mesh->GetDepthMaterial() == nullptr) continue;
		mesh->GetDepthMaterial()->Bind(false);
		mesh->RenderDepth();

	}

	RenderDepthChildren();

}

void NodeEntity::Render(bool sp) {

//	printf("Rendering NodeEntity.\n");
	//OutputDebugStringA("Rendering NodeEntity.\n");
	
	Engine::m_Node = this;


	if (m_Enabled) {
	
			for (auto mesh : m_Meshes) {
				mesh->GetMaterial()->Bind(sp);
				mesh->Render(sp);
				

			}


		RenderChildren(sp);
	}
}

void NodeEntity::SetMaterial(MaterialBase* material) {

	for (auto mesh : m_Meshes) {

		mesh->SetMaterial(material);

	}

}

bool NodeEntity::IsMeshIndex(Mesh3D* mesh, int idx)
{

	int i = 0;
	for (auto me : m_Meshes) {

		if (me == mesh) {
			if (i == idx) {
				return true;
			}
		}
		i++;
	}

	return false;

}

void NodeEntity::BuildGeo() {

	



	int b = 5;
	for (auto m : m_Meshes) {

		//m->BuildGeo();
		m->NeedsRebuild();
		
	}

}

void NodeEntity::ForceRebuild() {

	//BuildGeo();

	for (auto m : m_Meshes) {

	
		m->BuildGeo();

	}

}

Bounds* NodeEntity::GetBounds() {

	Bounds* res = new Bounds;
	res->Min = float3(10000, 10000, 10000);
	res->Max = float3(-10000, -10000, -10000);
	res->Centre = float3(0, 0, 0);

	for (auto m : m_Meshes) {


		auto world = float4x4::Identity();

		auto tris = m->GetTris();
		auto verts = m->GetVertices();

		for (auto v : verts) {

			float3 npos = v.position * world;
			if (npos.x < res->Min.x) res->Min.x = npos.x;
			if (npos.x > res->Max.x) res->Max.x = npos.x;
			if (npos.y < res->Min.y) res->Min.y = npos.y;
			if (npos.y > res->Max.y) res->Max.y = npos.y;
			if (npos.z < res->Min.z) res->Min.z = npos.z;
			if (npos.z > res->Max.z) res->Max.z = npos.z;

		}


	}

	res->Centre.x = res->Min.x + (res->Max.x - res->Min.x) / 2.0f;
	res->Centre.y = res->Min.y + (res->Max.y - res->Min.y) / 2.0f;
	res->Centre.z = res->Min.z + (res->Max.z - res->Min.z) / 2.0f;

	return res;
}

void NodeEntity::WriteNode(VFile* file) {

	file->WriteInt(2);
	file->WriteString(m_ResourcePath.c_str());
	file->WriteVec3(m_Position);
	file->WriteMatrix(m_Rotation);
	file->WriteVec3(m_Scale);
	file->WriteString(m_Name.c_str());


	file->WriteInt(m_Nodes.size());

	for (auto node : m_Nodes) {

		node->WriteNode(file);

	}

}

void NodeEntity::ReadNode(VFile* file) {

	m_ResourcePath = file->ReadString();
	m_Position = file->ReadVec3();
	m_Rotation = file->ReadMatrix();
	m_Scale = file->ReadVec3();
	m_Name = file->ReadString();

	Importer* import = new Importer;
	auto imp = (NodeEntity*)import->ImportNode(m_ResourcePath);


	for (auto mesh : imp->GetMeshes()) {

		AddMesh(mesh);

	}

}