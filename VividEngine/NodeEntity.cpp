#include "pch.h"
#include "NodeEntity.h"
#include "MaterialBase.h"
#include "MaterialDepth.h"
#include <windows.h>
#include "Mesh3D.h"
#include "Engine.h"

NodeEntity::NodeEntity() {

	

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