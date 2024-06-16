#include "pch.h"
#include "Animator.h"
#include "Bone.h"
#include "Animation.h"
#include "BoneInfo.h"

Animator::Animator(Animation* anim) {

	m_CurrentTime = 0.0;
	m_CurrentAnim = anim;
	
	for (int i = 0; i < 100; i++) {
		m_FinalBones.push_back(float4x4::Identity());
	}



}

void Animator::SetTime(float time) {

	m_CurrentTime = time;
	//CalcBones
	CalculateBoneTransform(m_CurrentAnim->GetRootNode(), float4x4::Identity());

}

void Animator::UpdateAnimation(float dt) {

	SetTime(dt);

}

void Animator::CalculateBoneTransform(AssimpNodeData* node, float4x4 transform) {

	std::string nodeName = node->name;
	float4x4 nodeTransform = node->transformation;

	Bone* bone = m_CurrentAnim->FindBone(nodeName);

	if (bone != nullptr) {

		bone->Update(m_CurrentTime);
		nodeTransform = bone->GetLocalTransform();
	}

	float4x4 globalTransform = nodeTransform * transform;
	auto boneInfo = m_CurrentAnim->GetBoneIDMap();
	if (boneInfo.count(nodeName) > 0)
	{
		int index = boneInfo[nodeName]->ID;
		float4x4 offset = boneInfo[nodeName]->Offset;
		m_FinalBones[index] = offset*globalTransform;// *offset;// nodeTransform; // float4x4::Identity();// offset* globalTransform;
	}

	for (int i = 0; i < node->childrenCount; i++) {
		CalculateBoneTransform(node->children[i],globalTransform);
	}

}

float Animator::GetLength() {
	return m_CurrentAnim->GetLength();
}