#include "pch.h"
#include "TerrainMesh.h"
#include "TerrainMeshBuffer.h"
#include "NodeTerrain.h"

void TerrainMesh::AddVertex(TerrainVertex vertex) {

	m_Vertices.push_back(vertex);

}

void TerrainMesh::AddTriangle(Triangle tri) {

	m_Triangles.push_back(tri);

}

void TerrainMesh::Build() {

	m_Buffer = new TerrainMeshBuffer(this);


}


void TerrainMesh::RebuildGeo() {

    if (m_Rebuild == false) return;
    printf("REBUILDING GEO: Tris:%d\n", GetTriangles().size());
    auto world = m_Owner->GetWorldMatrix();

    auto tris = GetTriangles();
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

    m_Rebuild = false;

}