#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include "BasicMath.hpp"

using namespace Diligent;

class Bone;
class NodeActor;
class BoneInfo;

class AssimpNodeData
{
public:
	float4x4 transformation;
	std::string name = "";
	int childrenCount = 0;
	std::vector<AssimpNodeData*> children;// = new List<AssimpNodeData>();



};


class Animation
{
public:

	Animation(aiScene* scene, aiAnimation* anim, NodeActor* actor);
	void ReadHeirarchyData(AssimpNodeData* root, aiNode* node);
	void ReadMissingBones(aiAnimation* anim, NodeActor* actor);
	Bone* FindBone(std::string name);
	AssimpNodeData* GetRootNode() {
		return m_RootNode;
	}
	std::map<std::string, BoneInfo*> GetBoneIDMap() {
		return m_BoneInfoMap;
	}
	float GetLength() {
		return m_Duration;
	}
private:
	
	float m_Duration = 0.0f;
	int m_TicksPerSecond = 0;
	std::string m_Name;
	std::string m_Path;
	float m_Priority = 1.0f;
	std::vector<Bone*> m_Bones;
	AssimpNodeData* m_RootNode = new AssimpNodeData();
	std::map<std::string, BoneInfo*> m_BoneInfoMap;


};

