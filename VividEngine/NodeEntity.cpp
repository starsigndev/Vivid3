#include "pch.h"
#include "NodeEntity.h"
#include "MaterialBase.h"

NodeEntity::NodeEntity() {

	m_Material = new MaterialBase;
	

}

void NodeEntity::AddMesh(Mesh3D* mesh) {

	m_Meshes.push_back(mesh);

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