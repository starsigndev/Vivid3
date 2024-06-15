#include "pch.h"
#include "Importer.h"
#include "VFile.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh3D.h"
#include "data.h"
#include "BasicMath.hpp"
#include "NodeEntity.h"
#include "MaterialMeshLight.h"
#include "MaterialDepth.h"
#include <filesystem>
#include "Texture2D.h"
namespace fs = std::filesystem;
using namespace Diligent;

std::string getDirectoryPath(const std::string& fullPath) {
    size_t lastSlashPos = fullPath.find_last_of("/\\");
    if (lastSlashPos == std::string::npos) {
        // No slash found, return an empty string or handle appropriately
        return "";
    }
    return fullPath.substr(0, lastSlashPos + 1);
}

std::string getFilename(const std::string& fullPath) {
    // Find the last occurrence of either '/' or '\\'
    size_t lastSlashPos = fullPath.find_last_of("/\\");

    if (lastSlashPos == std::string::npos) {
        // No slash found, the input is a filename itself
        return fullPath;
    }

    // Extract the filename from the full path
    return fullPath.substr(lastSlashPos + 1);
}

Node* Importer::ImportNode(std::string path) {

    Assimp::Importer importer;

    // Define import flags (e.g., to triangulate polygons)
    unsigned int flags = aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_GenNormals;

    // Load the scene from the file
    const aiScene* scene = importer.ReadFile(path, flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Error: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    NodeEntity* root = new NodeEntity;

    root->SetName(scene->mRootNode->mName.C_Str());

    std::string path_alone = getDirectoryPath(path);

    std::string mat_path = path_alone + "Material/";

    int b = 6;
    fs::create_directory(mat_path);


    std::vector<MaterialBase*> materials;

    for (int i = 0; i < scene->mNumMaterials; i++) {

        auto mat = scene->mMaterials[i];
        auto name = std::string(mat->GetName().C_Str());

        auto v_mat = new MaterialMeshLight;

        std::string check = mat_path + name + ".material";

        auto lmat = Engine::FindActiveMaterial(check);

        if (lmat != nullptr) {
            materials.push_back(lmat);
            continue;
        }

        if (VFile::Exists(check.c_str())) {

            v_mat->LoadMaterial(check);
            materials.push_back(v_mat);
            Engine::m_ActiveMaterials.push_back(v_mat);
            continue;

        }

        Engine::m_ActiveMaterials.push_back(v_mat);
        materials.push_back(v_mat);

        for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_DIFFUSE); ++j) {
            aiString str;

            mat->GetTexture(aiTextureType_DIFFUSE, j, &str);
            v_mat->SetDiffuse(new Texture2D(path_alone + getFilename(std::string(str.C_Str()))));
            //GLuint textureID = LoadTextureFromFile(directory + '/' + str.C_Str());
            std::cout << "Loaded diffuse texture ID:  for texture " << str.C_Str() << std::endl;
        }

        // Load specular textures
        for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_SPECULAR); ++j) {
            aiString str;
            mat->GetTexture(aiTextureType_SPECULAR, j, &str);
            v_mat->SetSpecular(new Texture2D(path_alone + std::string(str.C_Str())));
            //GLuint textureID = LoadTextureFromFile(directory + '/' + str.C_Str());
            std::cout << "Loaded specular texture ID: for texture " << str.C_Str() << std::endl;
        }

        // Load normal textures (height maps in Assimp terminology)
        for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_HEIGHT); ++j) {
            aiString str;

            mat->GetTexture(aiTextureType_HEIGHT, j, &str);
            v_mat->SetNormals(new Texture2D(path_alone + std::string(str.C_Str())));
            //GLuint textureID = LoadTextureFromFile(directory + '/' + str.C_Str());
            std::cout << "Loaded normal texture ID: for texture " << str.C_Str() << std::endl;
        }

        int b = 5;
        v_mat->SaveMaterial(mat_path + name + ".material");

    }
    
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
            vertex.texture = float3(aTex.x, aTex.y, aTex.z);
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
        
        mesh->SetMaterial(materials[aMesh->mMaterialIndex]);
        
        mesh->SetDepthMaterial(new MaterialDepth);


        root->AddMesh(mesh);
        mesh->BuildGeo();


    }

    return (Node*)root;


}