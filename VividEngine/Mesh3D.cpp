#include "pch.h"
#include "Mesh3D.h"
#include "MeshBuffer.h"

Mesh3D::Mesh3D() {

}

void Mesh3D::AddVertex(Vertex vertex,bool reset) {


	if (reset) {
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