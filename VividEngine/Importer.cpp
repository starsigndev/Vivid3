#include "pch.h"
#include "Importer.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh3D.h"
#include "data.h"
#include "BasicMath.hpp"
#include "NodeEntity.h"
#include "MaterialMeshLight.h"

using namespace Diligent;

Node* Importer::ImportNode(std::string path) {

    Assimp::Importer importer;

    // Define import flags (e.g., to triangulate polygons)
    unsigned int flags = aiProcess_CalcTangentSpace | aiProcess_Triangulate;

    // Load the scene from the file
    const aiScene* scene = importer.ReadFile(path, flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Error: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    NodeEntity* root = new NodeEntity;

    root->SetName(scene->mRootNode->mName.C_Str());

    for (int i = 0; i < scene->mNumMeshes; i++) {

        Mesh3D* mesh = new Mesh3D;
        const aiMesh* aMesh = scene->mMeshes[i];

        for (int v = 0; v < aMesh->mNumVertices; v++) {

            auto aVertex = aMesh->mVertices[v];
            auto aTex = aMesh->mTextureCoords[0][v];
            auto aNorm = aMesh->mNormals[v];
            auto aBiNorm = aMesh->mBitangents[v];
            auto aTan = aMesh->mTangents[v];

            Vertex vertex;
            vertex.position = float3(-aVertex.x, aVertex.z, aVertex.y);
            vertex.color = float4(1, 1, 1, 1);
            vertex.texture = float3(aTex.x, 1.0f-aTex.y, aTex.z);
            vertex.normal = float3(-aNorm.x, aNorm.z, aNorm.y);
            vertex.binormal = float3(-aBiNorm.x, aBiNorm.z, aBiNorm.y);
            vertex.tangent = float3(-aTan.x, aTan.z, aTan.y);

            mesh->AddVertex(vertex,true);

        }

        for (int t = 0; t < aMesh->mNumFaces; t++) {

            auto face = aMesh->mFaces[t];

            Triangle tri;

            tri.v0 = face.mIndices[0];
            tri.v1 = face.mIndices[1];
            tri.v2 = face.mIndices[2];

            mesh->AddTri(tri);

        }

        mesh->Build();

        mesh->SetMaterial(new MaterialMeshLight);

        root->AddMesh(mesh);

    }

    return (Node*)root;


}