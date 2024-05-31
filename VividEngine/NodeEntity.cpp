#include "pch.h"
#include "NodeEntity.h"
#include "MaterialBase.h"
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

void NodeEntity::Render() {

//	printf("Rendering NodeEntity.\n");
	//OutputDebugStringA("Rendering NodeEntity.\n");
	
	Engine::m_Node = this;


	for (auto light : Engine::m_Lights) {
		for (auto mesh : m_Meshes) {
			mesh->GetMaterial()->Bind();
			mesh->Render();

		}
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