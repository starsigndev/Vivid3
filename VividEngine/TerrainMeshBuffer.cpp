#include "pch.h"
#include "TerrainMeshBuffer.h"
#include "TerrainMesh.h"
#include "Engine.h"
#include "MeshBuffer.h"
#include "Mesh3D.h"
#include "Engine.h"
TerrainMeshBuffer::TerrainMeshBuffer(TerrainMesh* mesh) {



	float* data = new float[mesh->GetVertices().size() * 22];

	int i = 0;
	for (auto v : mesh->GetVertices()) {

		data[i++] = v.position.x;
		data[i++] = v.position.y;
		data[i++] = v.position.z;
		data[i++] = v.color.x;
		data[i++] = v.color.y;
		data[i++] = v.color.z;
		data[i++] = v.color.w;
		data[i++] = v.texture.x;
		data[i++] = v.texture.y;
		data[i++] = v.texture.z;
		data[i++] = v.normal.x;
		data[i++] = v.normal.y;
		data[i++] = v.normal.z;
		data[i++] = v.binormal.x;
		data[i++] = v.binormal.y;
		data[i++] = v.binormal.z;
		data[i++] = v.tangent.x;
		data[i++] = v.tangent.y;
		data[i++] = v.tangent.z;
		data[i++] = v.layercoord.x;
		data[i++] = v.layercoord.y;
		data[i++] = v.layercoord.z;

	}

	BufferDesc vbuf;
	vbuf.Name = "Mesh Buffer VB";
	vbuf.Usage = USAGE_IMMUTABLE;
	vbuf.BindFlags = BIND_VERTEX_BUFFER;
	vbuf.Size = (Uint64)(sizeof(TerrainVertex) * mesh->GetVertices().size());

	BufferData vdata;
	vdata.DataSize = vbuf.Size;
	vdata.pData = data;

	Engine::m_pDevice->CreateBuffer(vbuf, &vdata, &VertexBuffer);


	BufferDesc ibuf;

	ibuf.Name = "Mesh Buffer IB";
	ibuf.Usage = USAGE_IMMUTABLE;
	ibuf.BindFlags = BIND_INDEX_BUFFER;
	ibuf.Size = (Uint64)(sizeof(Uint32) * mesh->GetTriangles().size() * 3);

	Uint32* indices = new Uint32[mesh->GetTriangles().size() * 3];

	i = 0;
	for (auto t : mesh->GetTriangles())
	{
		indices[i++] = t.v0;
		indices[i++] = t.v2;
		indices[i++] = t.v1;
	}


	BufferData idata;
	idata.DataSize = ibuf.Size;
	idata.pData = indices;

	Engine::m_pDevice->CreateBuffer(ibuf, &idata, &IndexBuffer);

}