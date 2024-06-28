#include "pch.h"
#include "RTMesh.h"
#include "Mesh3D.h"
#include "NodeEntity.h"
#include "Engine.h"

RTMesh::RTMesh(Mesh3D* mesh) {


	
	m_Node = mesh->GetOwner();
	m_Mesh = mesh;
	BLASTriangleDesc Triangles;

	auto name = mesh->GetOwner()->GetFullName();

	m_Name = name;
	Triangles.GeometryName = name.c_str();
	Triangles.MaxVertexCount = mesh->GetVertices().size();
	Triangles.VertexValueType = VT_FLOAT32;
	Triangles.VertexComponentCount = 3;
	Triangles.MaxPrimitiveCount = mesh->GetTris().size();
	Triangles.IndexType = VT_UINT32;

	BottomLevelASDesc ASDesc;
	ASDesc.Name = mesh->GetOwner()->GetFullName().c_str();
	ASDesc.Flags = RAYTRACING_BUILD_AS_PREFER_FAST_TRACE;
	ASDesc.pTriangles = &Triangles;
	ASDesc.TriangleCount = 1;

	Engine::m_pDevice->CreateBLAS(ASDesc, &m_BLAS);

	
	//

	float* data = new float[mesh->GetVertices().size() * 27];

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
		data[i++] = v.bone_ids.x;
		data[i++] = v.bone_ids.y;
		data[i++] = v.bone_ids.z;
		data[i++] = v.bone_ids.w;
		data[i++] = v.bone_weights.x;
		data[i++] = v.bone_weights.y;
		data[i++] = v.bone_weights.z;
		data[i++] = v.bone_weights.w;

	}

	BufferDesc vbuf;
	vbuf.Name = "Mesh Buffer VB";
	vbuf.Usage = USAGE_IMMUTABLE;
	vbuf.BindFlags = BIND_VERTEX_BUFFER | BIND_RAY_TRACING;
	vbuf.Size = (Uint64)(sizeof(Vertex) * mesh->GetVertices().size());

	BufferData vdata;
	vdata.DataSize = vbuf.Size;
	vdata.pData = data;

	Engine::m_pDevice->CreateBuffer(vbuf, &vdata, &VertexBuffer);

	BufferDesc ibuf;

	ibuf.Name = "Mesh Buffer IB";
	ibuf.Usage = USAGE_IMMUTABLE;
	ibuf.BindFlags = BIND_INDEX_BUFFER | BIND_RAY_TRACING;
	ibuf.Size = (Uint64)(sizeof(Uint32) * mesh->GetTris().size() * 3);

	Uint32* indices = new Uint32[mesh->GetTris().size() * 3];

	i = 0;
	for (auto t : mesh->GetTris())
	{
		indices[i++] = t.v0;
		indices[i++] = t.v1;
		indices[i++] = t.v2;
	}


	BufferData idata;
	idata.DataSize = ibuf.Size;
	idata.pData = indices;

	Engine::m_pDevice->CreateBuffer(ibuf, &idata, &IndexBuffer);


	//

	RefCntAutoPtr<IBuffer> pScratchBuffer;
	{
		BufferDesc BuffDesc;
		BuffDesc.Name = "BLAS Scratch Buffer";
		BuffDesc.Usage = USAGE_DEFAULT;
		BuffDesc.BindFlags = BIND_RAY_TRACING;
		BuffDesc.Size = m_BLAS->GetScratchBufferSizes().Build;


		Engine::m_pDevice->CreateBuffer(BuffDesc, nullptr, &pScratchBuffer);
		VERIFY_EXPR(pScratchBuffer != nullptr);
	}


	//

	BLASBuildTriangleData TriangleData;
	TriangleData.GeometryName = Triangles.GeometryName;
	TriangleData.pVertexBuffer = VertexBuffer;
	TriangleData.VertexStride = sizeof(Vertex);
	TriangleData.VertexCount = Triangles.MaxVertexCount;
	TriangleData.VertexValueType = Triangles.VertexValueType;
	TriangleData.VertexComponentCount = Triangles.VertexComponentCount;
	TriangleData.pIndexBuffer = IndexBuffer;
	TriangleData.PrimitiveCount = Triangles.MaxPrimitiveCount;
	TriangleData.IndexType = Triangles.IndexType;
	TriangleData.Flags = RAYTRACING_GEOMETRY_FLAG_OPAQUE;

	BuildBLASAttribs Attribs;
	Attribs.pBLAS = m_BLAS;
	Attribs.pTriangleData = &TriangleData;
	Attribs.TriangleDataCount = 1;
	Attribs.pScratchBuffer = pScratchBuffer;

	Engine::m_pImmediateContext->BuildBLAS(Attribs);

}