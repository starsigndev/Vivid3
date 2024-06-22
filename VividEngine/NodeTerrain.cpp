#include "pch.h"
#include "NodeTerrain.h"
#include <vector>
#include "data.h"
#include "TerrainMesh.h"
#include "TerrainLayer.h"
#include "Texture2D.h"
#include "PixelMap.h"
#include "TerrainMeshBuffer.h"
#include "MaterialTerrain.h"
#include "MaterialTerrainDepth.h"

NodeTerrain::NodeTerrain(float width, float depth, float divisions, int layers)
{

    m_Material = new MaterialTerrain;
    m_DepthMaterial = new MaterialTerrainDepth;
	m_Width = width;
	m_Depth = depth;
	m_Divisions = divisions;
	CreateTerrain(layers);
    m_Name = "Terrain";
}

void NodeTerrain::CreateTerrain(int layers) {

	int widthSegments = (int)(m_Width * m_Divisions);
	int depthSegments = (int)(m_Depth * m_Divisions);
	float segmentWidth = m_Width / widthSegments;
	float segmentDepth = m_Depth / depthSegments;

	std::vector<TerrainVertex> vertices;
	std::vector<Triangle> triangles;

    for (int z = 0; z <= depthSegments; z++)
    {
        for (int x = 0; x <= widthSegments; x++)
        {
            float xPos = x * segmentWidth - m_Width / 2;
            float zPos = z * segmentDepth - m_Depth / 2;


            TerrainVertex vertex;

            vertex.position = float3(xPos, 0, zPos);
            vertex.texture = float3(((float)x / widthSegments) * 70, ((float)z / depthSegments) * 70,0);
            vertex.color = float4(1, 1, 1, 1);
            vertex.layercoord = float3((float)x / (float)widthSegments, (float)z / (float)depthSegments, 0);

          
            vertices.push_back(vertex);

            if (x < widthSegments && z < depthSegments)
            {
                int currentIndex = x + z * (widthSegments + 1);
                int nextIndex = (x + 1) + z * (widthSegments + 1);
                int bottomIndex = x + (z + 1) * (widthSegments + 1);
                int bottomNextIndex = (x + 1) + (z + 1) * (widthSegments + 1);

                Triangle t1;

                t1.v0 = currentIndex;
                t1.v1 = nextIndex;
                t1.v2 = bottomNextIndex;

                triangles.push_back(t1);

                Triangle t2;
                t2.v0 = currentIndex;
                t2.v1 = bottomNextIndex;
                t2.v2 = bottomIndex;

                triangles.push_back(t2);
            }
        }
    }
    m_Mesh = new TerrainMesh;
    m_Mesh->SetVertices(vertices);
    m_Mesh->SetTriangles(triangles);

    for (int i = 0; i < layers; i++)
    {
        TerrainLayer* layer1 = new TerrainLayer;
        if (i == 0)
        {


            layer1->SetColor(new Texture2D("edit/blank_layer.png",true));
        }
        else
        {

            layer1->SetColor(new Texture2D("engine\\white.png",true));
        }
        layer1->SetNormal(new Texture2D("engine/normal.png",true));
        layer1->SetSpecular(new Texture2D("engine/white.png", true));
        layer1->SetSpecular(new Texture2D("engine/white.png"));
        //layer1.NormalMap = new Texture.Texture2D("engine\\maps\\blanknormal.jpg");
        //layer1.SpecularMap = new Texture.Texture2D("engine\\maps\\white.png");
        layer1->SetPixels(new PixelMap(1024, 1024));


        if (i == 0)
        {
            //layer1->SetLayerMap(new Texture2D("engine\\white.png"));
            auto pixmap = new PixelMap(1024, 1024, float4(1, 1, 1, 1));
            layer1->SetPixels(pixmap);
            layer1->SetLayerMap(new Texture2D(pixmap->GetWidth(), pixmap->GetHeight(), pixmap->GetData(), 4));
            //
            // layer1->SetPixels()

        }
        else
        {

            layer1->SetLayerMap(new Texture2D(1024, 1024, layer1->GetPixels()->GetData(),4));
            //  layer1.LayerMap = new Texture.Texture2D("engine\\terrain\\layer1.png");
        }
        m_Layers.push_back(layer1);
    }
    m_Mesh->CalculateNormals();
    m_Mesh->Build();
    m_Mesh->SetOwner(this);
    

}

void NodeTerrain::Render(bool sp) {

    Engine::m_Node = this;
    


    auto m_Buffer = m_Mesh->GetBuffer();

    int ii = 0;
    for (auto layer : m_Layers) {

        m_Material->SetDiffuse(layer->GetColor());
        m_Material->SetNormals(layer->GetNormal());
        m_Material->SetSpecular(layer->GetSpec());
        m_Material->SetLayerMap(layer->GetLayerMap());
        m_Material->SetLayerIndex(ii);
        m_Material->Bind(sp);
       
        ii++;
        IBuffer* pBuffs[] = { m_Buffer->GetVertexBuffer() };
        Uint64 offsets = 0;
        Engine::m_pImmediateContext->SetVertexBuffers(0, 1, pBuffs, &offsets, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
        Engine::m_pImmediateContext->SetIndexBuffer(m_Buffer->GetTriangleBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

        if (sp) {
            Engine::m_pImmediateContext->CommitShaderResources(m_Material->GetSecondPassSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        }
        else {
            Engine::m_pImmediateContext->CommitShaderResources(m_Material->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        }
        DrawIndexedAttribs attrib;
        attrib.IndexType = VALUE_TYPE::VT_UINT32;
        attrib.NumIndices = m_Mesh->GetTriangles().size() * 3;
        attrib.Flags = DRAW_FLAG_VERIFY_ALL;
        Engine::m_pImmediateContext->DrawIndexed(attrib);


    }

}

TerrainMesh* NodeTerrain::GetMesh() {

    return m_Mesh;

}

Bounds NodeTerrain::GetTerrainBounds() {

    auto verts = m_Mesh->GetVertices();

    float3 min, max;

    for (auto v : verts) {

        auto pos = v.position;
        min = Diligent::min(min, pos);
        max = Diligent::max(max, pos);

    }

    Bounds res;
    res.Min = min;
    res.Max = max;
    res.Centre = min + ((max / min) / 2);
    return res;
}

void NodeTerrain::RenderDepth() {
    //return;

    //m_DepthMaterial->Bind(false);
    //m_Material->SetDiffuse(layer->GetColor());
    //m_Material->SetLayerMap(layer->GetLayerMap());
    Engine::m_Node = this;
    
    m_DepthMaterial->Bind(false);




    IBuffer* pBuffs[] = { m_Mesh->GetBuffer()->GetVertexBuffer() };
    Uint64 offsets = 0;
    Engine::m_pImmediateContext->SetVertexBuffers(0, 1, pBuffs, &offsets, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
    Engine::m_pImmediateContext->SetIndexBuffer(m_Mesh->GetBuffer()->GetTriangleBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    //if (sp) {

     //   Engine::m_pImmediateContext->CommitShaderResources(m_Material->GetSecondPassSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
   // }
   // else {
        Engine::m_pImmediateContext->CommitShaderResources(m_DepthMaterial->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    //}
    DrawIndexedAttribs attrib;
    attrib.IndexType = VALUE_TYPE::VT_UINT32;
    attrib.NumIndices = m_Mesh->GetTriangles().size() * 3;
    attrib.Flags = DRAW_FLAG_VERIFY_ALL;
    Engine::m_pImmediateContext->DrawIndexed(attrib);



}