#include "pch.h"
#include "Mesh3D.h"
#include "MeshBuffer.h"
#include "Engine.h"
#include "MaterialBase.h"
#include "MaterialMeshLight.h"
#include "MaterialDepth.h"
#include "NodeEntity.h"
#include <immintrin.h>
#include <intrin.h>
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


void transform_points_avx512(const std::vector<float3>& points, const float4x4& matrix, std::vector<float3>& transformed_points) {
	size_t size = points.size();
	transformed_points.resize(size);

	// Broadcast matrix rows once before the loop
	__m512 row0 = _mm512_set_ps(matrix.m03, matrix.m02, matrix.m01, matrix.m00, matrix.m03, matrix.m02, matrix.m01, matrix.m00, matrix.m03, matrix.m02, matrix.m01, matrix.m00, matrix.m03, matrix.m02, matrix.m01, matrix.m00);
	__m512 row1 = _mm512_set_ps(matrix.m13, matrix.m12, matrix.m11, matrix.m10, matrix.m13, matrix.m12, matrix.m11, matrix.m10, matrix.m13, matrix.m12, matrix.m11, matrix.m10, matrix.m13, matrix.m12, matrix.m11, matrix.m10);
	__m512 row2 = _mm512_set_ps(matrix.m23, matrix.m22, matrix.m21, matrix.m20, matrix.m23, matrix.m22, matrix.m21, matrix.m20, matrix.m23, matrix.m22, matrix.m21, matrix.m20, matrix.m23, matrix.m22, matrix.m21, matrix.m20);
	__m512 row3 = _mm512_set_ps(matrix.m33, matrix.m32, matrix.m31, matrix.m30, matrix.m33, matrix.m32, matrix.m31, matrix.m30, matrix.m33, matrix.m32, matrix.m31, matrix.m30, matrix.m33, matrix.m32, matrix.m31, matrix.m30);

	for (size_t i = 0; i + 4 <= size; i += 4) {
		// Load four points
		__m512 px = _mm512_set_ps(points[i + 3].x, points[i + 3].x, points[i + 3].x, points[i + 3].x,
			points[i + 2].x, points[i + 2].x, points[i + 2].x, points[i + 2].x,
			points[i + 1].x, points[i + 1].x, points[i + 1].x, points[i + 1].x,
			points[i].x, points[i].x, points[i].x, points[i].x);
		__m512 py = _mm512_set_ps(points[i + 3].y, points[i + 3].y, points[i + 3].y, points[i + 3].y,
			points[i + 2].y, points[i + 2].y, points[i + 2].y, points[i + 2].y,
			points[i + 1].y, points[i + 1].y, points[i + 1].y, points[i + 1].y,
			points[i].y, points[i].y, points[i].y, points[i].y);
		__m512 pz = _mm512_set_ps(points[i + 3].z, points[i + 3].z, points[i + 3].z, points[i + 3].z,
			points[i + 2].z, points[i + 2].z, points[i + 2].z, points[i + 2].z,
			points[i + 1].z, points[i + 1].z, points[i + 1].z, points[i + 1].z,
			points[i].z, points[i].z, points[i].z, points[i].z);
		__m512 pw = _mm512_set1_ps(1.0f);

		// Compute transformed x
		__m512 result_x = _mm512_fmadd_ps(px, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m00)),
			_mm512_fmadd_ps(py, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m01)),
				_mm512_fmadd_ps(pz, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m02)),
					_mm512_mul_ps(pw, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m03))))));

		// Compute transformed y
		__m512 result_y = _mm512_fmadd_ps(px, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m10)),
			_mm512_fmadd_ps(py, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m11)),
				_mm512_fmadd_ps(pz, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m12)),
					_mm512_mul_ps(pw, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m13))))));

		// Compute transformed z
		__m512 result_z = _mm512_fmadd_ps(px, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m20)),
			_mm512_fmadd_ps(py, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m21)),
				_mm512_fmadd_ps(pz, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m22)),
					_mm512_mul_ps(pw, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m23))))));

		// Store results
		float* xRes = reinterpret_cast<float*>(&result_x);
		float* yRes = reinterpret_cast<float*>(&result_y);
		float* zRes = reinterpret_cast<float*>(&result_z);

		transformed_points[i] = { xRes[0], yRes[0], zRes[0] };
		transformed_points[i + 1] = { xRes[4], yRes[4], zRes[4] };
		transformed_points[i + 2] = { xRes[8], yRes[8], zRes[8] };
		transformed_points[i + 3] = { xRes[12], yRes[12], zRes[12] };
	}

	// Handle the remaining points if size is not a multiple of 4
	for (size_t i = size - (size % 4); i < size; ++i) {
		__m512 px = _mm512_set1_ps(points[i].x);
		__m512 py = _mm512_set1_ps(points[i].y);
		__m512 pz = _mm512_set1_ps(points[i].z);
		__m512 pw = _mm512_set1_ps(1.0f);

		__m512 result_x = _mm512_fmadd_ps(px, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m00)),
			_mm512_fmadd_ps(py, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m01)),
				_mm512_fmadd_ps(pz, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m02)),
					_mm512_mul_ps(pw, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m03))))));

		__m512 result_y = _mm512_fmadd_ps(px, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m10)),
			_mm512_fmadd_ps(py, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m11)),
				_mm512_fmadd_ps(pz, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m12)),
					_mm512_mul_ps(pw, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m13))))));

		__m512 result_z = _mm512_fmadd_ps(px, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m20)),
			_mm512_fmadd_ps(py, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m21)),
				_mm512_fmadd_ps(pz, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m22)),
					_mm512_mul_ps(pw, _mm512_broadcastss_ps(_mm_load_ss(&matrix.m23))))));

		float* xRes = reinterpret_cast<float*>(&result_x);
		float* yRes = reinterpret_cast<float*>(&result_y);
		float* zRes = reinterpret_cast<float*>(&result_z);

		transformed_points[i] = { xRes[0], yRes[0], zRes[0] };
	}
}
void transform_points_avx(const std::vector<float3>& points, const float4x4& matrix, std::vector<float3>& transformed_points) {
	size_t size = points.size();
	transformed_points.resize(size);

	// Broadcast matrix rows once before the loop
	__m256 row0 = _mm256_set_ps(matrix.m03, matrix.m02, matrix.m01, matrix.m00, matrix.m03, matrix.m02, matrix.m01, matrix.m00);
	__m256 row1 = _mm256_set_ps(matrix.m13, matrix.m12, matrix.m11, matrix.m10, matrix.m13, matrix.m12, matrix.m11, matrix.m10);
	__m256 row2 = _mm256_set_ps(matrix.m23, matrix.m22, matrix.m21, matrix.m20, matrix.m23, matrix.m22, matrix.m21, matrix.m20);
	__m256 row3 = _mm256_set_ps(matrix.m33, matrix.m32, matrix.m31, matrix.m30, matrix.m33, matrix.m32, matrix.m31, matrix.m30);

	for (size_t i = 0; i + 2 <= size; i += 2) {
		// Load two points
		__m256 px = _mm256_set_ps(points[i + 1].x, points[i + 1].x, points[i + 1].x, points[i + 1].x,
			points[i].x, points[i].x, points[i].x, points[i].x);
		__m256 py = _mm256_set_ps(points[i + 1].y, points[i + 1].y, points[i + 1].y, points[i + 1].y,
			points[i].y, points[i].y, points[i].y, points[i].y);
		__m256 pz = _mm256_set_ps(points[i + 1].z, points[i + 1].z, points[i + 1].z, points[i + 1].z,
			points[i].z, points[i].z, points[i].z, points[i].z);
		__m256 pw = _mm256_set1_ps(1.0f);

		// Compute transformed x
		__m256 result_x = _mm256_fmadd_ps(px, _mm256_broadcast_ss(&matrix.m00),
			_mm256_fmadd_ps(py, _mm256_broadcast_ss(&matrix.m01),
				_mm256_fmadd_ps(pz, _mm256_broadcast_ss(&matrix.m02),
					_mm256_mul_ps(pw, _mm256_broadcast_ss(&matrix.m03)))));

		// Compute transformed y
		__m256 result_y = _mm256_fmadd_ps(px, _mm256_broadcast_ss(&matrix.m10),
			_mm256_fmadd_ps(py, _mm256_broadcast_ss(&matrix.m11),
				_mm256_fmadd_ps(pz, _mm256_broadcast_ss(&matrix.m12),
					_mm256_mul_ps(pw, _mm256_broadcast_ss(&matrix.m13)))));

		// Compute transformed z
		__m256 result_z = _mm256_fmadd_ps(px, _mm256_broadcast_ss(&matrix.m20),
			_mm256_fmadd_ps(py, _mm256_broadcast_ss(&matrix.m21),
				_mm256_fmadd_ps(pz, _mm256_broadcast_ss(&matrix.m22),
					_mm256_mul_ps(pw, _mm256_broadcast_ss(&matrix.m23)))));

		// Store results
		float* xRes = reinterpret_cast<float*>(&result_x);
		float* yRes = reinterpret_cast<float*>(&result_y);
		float* zRes = reinterpret_cast<float*>(&result_z);

		transformed_points[i] = { xRes[0], yRes[0], zRes[0] };
		transformed_points[i + 1] = { xRes[4], yRes[4], zRes[4] };
	}

	// Handle the remaining point if size is odd
	if (size % 2 != 0) {
		size_t i = size - 1;
		__m256 px = _mm256_set1_ps(points[i].x);
		__m256 py = _mm256_set1_ps(points[i].y);
		__m256 pz = _mm256_set1_ps(points[i].z);
		__m256 pw = _mm256_set1_ps(1.0f);

		__m256 result_x = _mm256_fmadd_ps(px, _mm256_broadcast_ss(&matrix.m00),
			_mm256_fmadd_ps(py, _mm256_broadcast_ss(&matrix.m01),
				_mm256_fmadd_ps(pz, _mm256_broadcast_ss(&matrix.m02),
					_mm256_mul_ps(pw, _mm256_broadcast_ss(&matrix.m03)))));

		__m256 result_y = _mm256_fmadd_ps(px, _mm256_broadcast_ss(&matrix.m10),
			_mm256_fmadd_ps(py, _mm256_broadcast_ss(&matrix.m11),
				_mm256_fmadd_ps(pz, _mm256_broadcast_ss(&matrix.m12),
					_mm256_mul_ps(pw, _mm256_broadcast_ss(&matrix.m13)))));

		__m256 result_z = _mm256_fmadd_ps(px, _mm256_broadcast_ss(&matrix.m20),
			_mm256_fmadd_ps(py, _mm256_broadcast_ss(&matrix.m21),
				_mm256_fmadd_ps(pz, _mm256_broadcast_ss(&matrix.m22),
					_mm256_mul_ps(pw, _mm256_broadcast_ss(&matrix.m23)))));

		float* xRes = reinterpret_cast<float*>(&result_x);
		float* yRes = reinterpret_cast<float*>(&result_y);
		float* zRes = reinterpret_cast<float*>(&result_z);

		transformed_points[i] = { xRes[0], yRes[0], zRes[0] };
	}

}

void transform_points_avx2(const std::vector<float3>& points, const float4x4& matrix, std::vector<float3>& transformed_points) {
	size_t size = points.size();
	transformed_points.resize(size);

	// Unroll the loop by 8 for better performance
	for (size_t i = 0; i < size; i += 8) {
		// Load points into vectors
		__m256 px = _mm256_set_ps(points[i + 7].x, points[i + 6].x, points[i + 5].x, points[i + 4].x,
			points[i + 3].x, points[i + 2].x, points[i + 1].x, points[i].x);
		__m256 py = _mm256_set_ps(points[i + 7].y, points[i + 6].y, points[i + 5].y, points[i + 4].y,
			points[i + 3].y, points[i + 2].y, points[i + 1].y, points[i].y);
		__m256 pz = _mm256_set_ps(points[i + 7].z, points[i + 6].z, points[i + 5].z, points[i + 4].z,
			points[i + 3].z, points[i + 2].z, points[i + 1].z, points[i].z);

		// Broadcast matrix rows
		__m256 m0 = _mm256_set_ps(matrix.m03, matrix.m02, matrix.m01, matrix.m00,
			matrix.m03, matrix.m02, matrix.m01, matrix.m00);
		__m256 m1 = _mm256_set_ps(matrix.m13, matrix.m12, matrix.m11, matrix.m10,
			matrix.m13, matrix.m12, matrix.m11, matrix.m10);
		__m256 m2 = _mm256_set_ps(matrix.m23, matrix.m22, matrix.m21, matrix.m20,
			matrix.m23, matrix.m22, matrix.m21, matrix.m20);

		// Compute transformed points
		__m256 tx = _mm256_fmadd_ps(px, m0, _mm256_set1_ps(matrix.m30));
		__m256 ty = _mm256_fmadd_ps(px, m1, _mm256_set1_ps(matrix.m31));
		__m256 tz = _mm256_fmadd_ps(px, m2, _mm256_set1_ps(matrix.m32));

		tx = _mm256_fmadd_ps(py, m0, tx);
		ty = _mm256_fmadd_ps(py, m1, ty);
		tz = _mm256_fmadd_ps(py, m2, tz);

		tx = _mm256_fmadd_ps(pz, m0, tx);
		ty = _mm256_fmadd_ps(pz, m1, ty);
		tz = _mm256_fmadd_ps(pz, m2, tz);

		// Store results
		_mm256_storeu_ps(&transformed_points[i].x, tx);
		_mm256_storeu_ps(&transformed_points[i].y, ty);
		_mm256_storeu_ps(&transformed_points[i].z, tz);
	}

	// Handle the remaining points (if any) sequentially
	for (size_t i = size - (size % 8); i < size; ++i) {
		transformed_points[i].x = points[i].x * matrix.m00 + points[i].y * matrix.m01 + points[i].z * matrix.m02 + matrix.m03;
		transformed_points[i].y = points[i].x * matrix.m10 + points[i].y * matrix.m11 + points[i].z * matrix.m12 + matrix.m13;
		transformed_points[i].z = points[i].x * matrix.m20 + points[i].y * matrix.m21 + points[i].z * matrix.m22 + matrix.m23;
	}
}
bool supports_avx512() {
	int cpuInfo[4];
	__cpuid(cpuInfo, 0);
	int numIds = cpuInfo[0];

	if (numIds >= 7) {
		__cpuidex(cpuInfo, 7, 0);
		return (cpuInfo[1] & (1 << 16)) != 0;  // AVX512F is bit 16 of EBX
	}

	return false;
}

void Mesh3D::BuildGeo() {

	if (n_NeedsRebuild == false) return;
	//printf("REBUILDING GEO: Tris:%d\n",GetTris().size());
	auto world = m_Owner->GetWorldMatrix().Transpose();

	int stime = clock();



	if (m_Build.size() == 0) {
		auto tris = GetTris();
		auto verts = GetVertices();

		m_Build.clear();


		for (auto t : tris) {

			float3 v0 = verts[t.v0].position;// *world;
			float3 v1 = verts[t.v1].position;// *world;
			float3 v2 = verts[t.v2].position;// *world;
			m_Build.push_back(v0);
			m_Build.push_back(v1);
			m_Build.push_back(v2);


		}
	}
	if (m_UseBuild.size() > 0)
	{
		m_UseBuild.clear();
	
	}
	
	if (supports_avx512()) {
		transform_points_avx512(m_Build, world, m_UseBuild);
	}
	else {
		transform_points_avx(m_Build, world, m_UseBuild);
	}

	int et = clock();

	printf("TimeGEO:%d\n", et - stime);

	n_NeedsRebuild = false;

}
