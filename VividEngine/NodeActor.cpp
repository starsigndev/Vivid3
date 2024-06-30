#include "pch.h"
#include "NodeActor.h"
#include "Mesh3D.h"
#include "MaterialActorLight.h"
#include "MaterialActorDepth.h"
#include "BasicMath.hpp"
#include "Animator.h"
#include "Engine.h"
#include "Bounds.h"
using namespace Diligent;



float3 atov(aiVector3D v)
{

	return float3(v.x, v.y, v.z);

}

Diligent::float4x4 atov(const aiMatrix4x4& assimpMat) {
	Diligent::float4x4 diligentMat;

	diligentMat.m00 = assimpMat.a1; diligentMat.m01 = assimpMat.a2; diligentMat.m02 = assimpMat.a3; diligentMat.m03 = assimpMat.a4;
	diligentMat.m10 = assimpMat.b1; diligentMat.m11 = assimpMat.b2; diligentMat.m12 = assimpMat.b3; diligentMat.m13 = assimpMat.b4;
	diligentMat.m20 = assimpMat.c1; diligentMat.m21 = assimpMat.c2; diligentMat.m22 = assimpMat.c3; diligentMat.m23 = assimpMat.c4;
	diligentMat.m30 = assimpMat.d1; diligentMat.m31 = assimpMat.d2; diligentMat.m32 = assimpMat.d3; diligentMat.m33 = assimpMat.d4;

	return diligentMat.Transpose();
}

Mesh3D* NodeActor::ProcessMesh(aiMesh* mesh, aiScene* scene, bool buf_cre)
{

	auto res = new Mesh3D();
	res->SetOwner(this);

	for (int i = 0; i < mesh->mNumVertices; i++) {

		Vertex v;

		v.position = atov(mesh->mVertices[i]);
		v.normal = atov(mesh->mNormals[i]);
		v.tangent = atov(mesh->mTangents[i]);
		v.binormal = atov(mesh->mBitangents[i]);
		v.texture = atov(mesh->mTextureCoords[0][i]);
		v.texture.y = 1.0f - v.texture.y;
		v.color = float4(1, 1, 1, 1);
		res->AddVertex(v,true);

	}

	ExtractBoneWeights(res, mesh, scene);

	m_Meshes.push_back(res);

	for (int i = 0; i < mesh->mNumFaces; i++) {
		Triangle t;
		t.v0 = mesh->mFaces[i].mIndices[0];
		t.v1 = mesh->mFaces[i].mIndices[1];
		t.v2 = mesh->mFaces[i].mIndices[2];
		
		res->AddTri(t);

		Triangle t2;

		t2.v0 = t.v0;
		t2.v1 = t.v2;
		t2.v2 = t.v1;


	}

	if (buf_cre) {
		res->Build();
	}

	return res;
}

void NodeActor::ExtractBoneWeights(Mesh3D* mesh, aiMesh* amesh, aiScene* scene) {

	for (int i = 0; i < amesh->mNumBones; i++) {

		int boneID = -1;
		std::string name = amesh->mBones[i]->mName.C_Str();
		if (m_BoneInfoMap.count(name) == 0) {

			BoneInfo* bone = new BoneInfo;
			bone->ID = m_BoneCounter;
			bone->Offset =  atov(amesh->mBones[i]->mOffsetMatrix);
			m_BoneInfoMap[name] = bone;
			boneID = m_BoneCounter;
			m_BoneCounter++;

		}
		else {
			boneID = m_BoneInfoMap[name]->ID;
		}
		
		auto weights = amesh->mBones[i]->mWeights;
		int num_weights = amesh->mBones[i]->mNumWeights;
		
		for (int weightIndex = 0; weightIndex < num_weights; weightIndex++)
		{
			int vert_id = weights[weightIndex].mVertexId;
			float weight = weights[weightIndex].mWeight;
			auto v = SetVertexBoneData(mesh->GetVertex(vert_id), i, weight);
			mesh->SetVertex(vert_id, v);
		}

	
	}


}

Vertex NodeActor::SetVertexBoneData(Vertex vertex, int boneID, float weight) {

	if (vertex.bone_ids.x < 0)
	{
		vertex.bone_ids.x = boneID;
		vertex.bone_weights.x = weight;
		return vertex;
	}
	if (vertex.bone_ids.y < 0)
	{
		vertex.bone_ids.y= boneID;
		vertex.bone_weights.y = weight;
		return vertex;
	}
	if (vertex.bone_ids.z < 0)
	{
		vertex.bone_ids.z = boneID;
		vertex.bone_weights.z = weight;
		return vertex;
	}
	if (vertex.bone_ids.w < 0)
	{
		vertex.bone_ids.w = boneID;
		vertex.bone_weights.w = weight;
		return vertex;
	}
	return vertex;
}

void NodeActor::Update() {

	int b = 5;
	dt = dt + 0.1f;
	if (dt > m_Animator->GetLength()) {
		dt = 0;
	}
	m_Animator->UpdateAnimation(dt);
	auto bones = m_Animator->GetBones();
	for (auto msh : m_Meshes) {
		auto ml = (MaterialActorLight*)msh->GetMaterial();
		ml->SetBones(bones);
		auto md = (MaterialActorDepth*)msh->GetDepthMaterial();
		md->SetBones(bones);

	}

}

void NodeActor::Render(bool sp) {

	//	printf("Rendering NodeEntity.\n");
		//OutputDebugStringA("Rendering NodeEntity.\n");

	Engine::m_Node = this;
	if (m_Bounds == nullptr) {
		m_Bounds = GetBounds();
	}

	auto world = GetWorldMatrix();

	auto center = m_Bounds->Centre * world;
	auto size = m_Bounds->Size() * GetScale();


	if (Engine::m_Camera->InView(center, size) > 0) {

		if (m_Enabled) {

			for (auto mesh : m_Meshes) {
				mesh->GetMaterial()->Bind(sp);
				mesh->Render(sp);


			}

		}
	}
	else {
		//printf("Culled Actor\n");
	}
	RenderChildren(sp);


}

std::vector<float4x4> NodeActor::GetBones() {
	return m_Animator->GetBones();
}