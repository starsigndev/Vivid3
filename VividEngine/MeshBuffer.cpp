#include "pch.h"
#include "MeshBuffer.h"
#include "Mesh3D.h"
#include "Engine.h"

MeshBuffer::MeshBuffer() {

	m_Mesh = nullptr;

}

void MeshBuffer::SetMesh(Mesh3D* mesh) {

	m_Mesh = mesh;

}

void MeshBuffer::Build() {

	BufferDesc vbuf;
	vbuf.Name = "Mesh Buffer VB";
	vbuf.Usage = USAGE_IMMUTABLE;
	vbuf.BindFlags = BIND_VERTEX_BUFFER;
	vbuf.Size = sizeof(Vertex) * m_Mesh->GetVertices().size();

	BufferData vdata;
	vdata.DataSize = vbuf.Size;
	vdata.pData = m_Mesh->GetVertices().data();

	Engine::m_pDevice->CreateBuffer(vbuf, &vdata, &VertexBuffer);

	BufferDesc ibuf;

	ibuf.Name = "Mesh Buffer IB";
	ibuf.Usage = USAGE_IMMUTABLE;
	ibuf.BindFlags = BIND_INDEX_BUFFER;
	ibuf.Size = (Uint64)(sizeof(uint) * m_Mesh->GetTris().size() * 3);

	BufferData idata;
	idata.DataSize = ibuf.Size;
	idata.pData = m_Mesh->GetTris().data();

	Engine::m_pDevice->CreateBuffer(ibuf, &idata, &IndexBuffer);

}