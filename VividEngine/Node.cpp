#include "pch.h"
#include "Node.h"
#include "Engine.h"
#include "MathsHelp.h"
#ifndef M_PI_2

#define M_PI_2 1.57079632679489661923 // π/2

#endif

#include "BasicMath.hpp"
#include "ScriptHost.h"
#include "VClass.h"
#include "VVar.h"
#include "FileHelp.h"
#include "VFunction.h"
#include "VFile.h"
bool first_node = true;
using namespace Diligent;

float4x4 CreateRotationMatrix(float pitch, float yaw, float roll)
{
	// Convert degrees to radians


	float cosPitch = std::cos(pitch);
	float sinPitch = std::sin(pitch);
	float cosYaw = std::cos(yaw);
	float sinYaw = std::sin(yaw);
	float cosRoll = std::cos(roll);
	float sinRoll = std::sin(roll);

	float4x4 rotationMatrix;
	rotationMatrix[0][0] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
	rotationMatrix[0][1] = cosRoll * sinYaw * sinPitch - cosYaw * sinRoll;
	rotationMatrix[0][2] = cosPitch * sinYaw;
	rotationMatrix[0][3] = 0.0f;

	rotationMatrix[1][0] = cosPitch * sinRoll;
	rotationMatrix[1][1] = cosPitch * cosRoll;
	rotationMatrix[1][2] = -sinPitch;
	rotationMatrix[1][3] = 0.0f;

	rotationMatrix[2][0] = sinYaw * sinRoll * cosPitch - cosRoll * cosYaw;
	rotationMatrix[2][1] = cosYaw * sinRoll * cosPitch + sinYaw * cosRoll;
	rotationMatrix[2][2] = cosYaw * cosPitch;
	rotationMatrix[2][3] = 0.0f;

	rotationMatrix[3][0] = 0.0f;
	rotationMatrix[3][1] = 0.0f;
	rotationMatrix[3][2] = 0.0f;
	rotationMatrix[3][3] = 1.0f;

	return rotationMatrix;
}

void RotationMatrixToEulerAngles(const float4x4& rotationMatrix, float& pitch, float& yaw, float& roll)
{
	if (std::abs(rotationMatrix[2][0]) < 1.0f)
	{
		yaw = std::atan2(rotationMatrix[1][0], rotationMatrix[0][0]);
		pitch = std::asin(-rotationMatrix[2][0]);
		roll = std::atan2(rotationMatrix[2][1], rotationMatrix[2][2]);
	}
	else
	{
		// Gimbal lock case
		yaw = 0.0f;
		if (rotationMatrix[2][0] <= -1.0f)
		{
			pitch = M_PI_2; // 90 degrees
			roll = std::atan2(rotationMatrix[0][1], rotationMatrix[0][2]);
		}
		else
		{
			pitch = -M_PI_2; // -90 degrees
			roll = std::atan2(-rotationMatrix[0][1], -rotationMatrix[0][2]);
		}
	}

}


VVar* CF_Debug(const std::vector<VVar*>& args)
{
	int b = 5;

	std::vector<VVar*> vec(args);

	printf("Debug:");
	printf(vec[0]->ToString().c_str());
	printf("\n");

	//printf("Debug1:%d\n",vec[0]->ToInt());

 //   printf("Debug2:%f\n", vec[0]->ToFloat());

	return nullptr;
}

VVar* CF_NodeGetPosition(const std::vector<VVar*>& args)
{
	auto c = (Node*)args[0]->ToC();
	int b = 5;

	auto pos = c->GetPosition();

	VVar* res = Engine::m_ScriptHost->CRVec3(pos.x, pos.y, pos.z);

	return res;
}

VVar* CF_NodeSetPosition(const std::vector<VVar*>& args)
{
	auto c = (Node*)args[0]->ToC();

	float3 v;

	v.x= args[1]->GetClassValue()->FindVar("X")->ToFloat();
	v.y = args[1]->GetClassValue()->FindVar("Y")->ToFloat();
	v.z = args[1]->GetClassValue()->FindVar("Z")->ToFloat();





	c->SetPosition(v);

	return nullptr;
}


VVar* CF_TurnNode(const std::vector<VVar*>& args)
{
	int b = 5;

	std::vector<VVar*> vec(args);
	
	//printf("Turn Node!\n");
	auto node = (Node*)vec[0]->ToC();

	node->Turn(vec[1]->ToFloat(), vec[2]->ToFloat(), vec[3]->ToFloat(),false);

	//printf("Debug1:%d\n",vec[0]->ToInt());

 //   printf("Debug2:%f\n", vec[0]->ToFloat());

	return nullptr;
}


Node::Node() {

	if (first_node) {

		Engine::m_ScriptHost->AddCFunction("TurnNode", CF_TurnNode);
		Engine::m_ScriptHost->AddCFunction("Debug", CF_Debug);
		Engine::m_ScriptHost->AddCFunction("GetPositionNode", CF_NodeGetPosition);
		Engine::m_ScriptHost->AddCFunction("SetPositionNode", CF_NodeSetPosition);
		first_node = false;
	}
	m_Rotation = float4x4::Identity();
	m_Position = float3(0, 0, 0);
	m_Scale = float3(1, 1, 1);



	

	int b = 5;
}

void Node::AddNode(Node* node) {

	m_Nodes.push_back(node);
	node->SetRoot(this);

}

int Node::NodesCount() {

	return m_Nodes.size();

}

Node* Node::GetNode(int index) {

	return m_Nodes[index];

}

std::vector<Node*> Node::GetNodes()
{

	return m_Nodes;

}

void Node::SetPosition(float3 position) {

	if (position.x == m_Position.x && position.y == m_Position.y && position.z == m_Position.z)
	{
		return;
	}
	m_Position = position;
	
	
	BuildGeo();
	Updated();

}

float3 Node::GetPosition() {

	return m_Position;

}

void Node::SetRotation(float pitch, float yaw, float roll,bool edit) {

	yaw = MathsHelp::Deg2Rad(yaw);
	pitch = MathsHelp::Deg2Rad(pitch);
	roll = MathsHelp::Deg2Rad(roll);
	BuildGeo();

	//m_Rotation = CreateRotationMatrix(pitch, yaw, roll);

	if (edit) {
		m_Rotation = float4x4::RotationY(yaw) * float4x4::RotationX(pitch) * float4x4::RotationZ(roll);
	}
	else {
		m_Rotation = float4x4::RotationX(pitch) * float4x4::RotationY(yaw) * float4x4::RotationZ(roll);
	}
	Updated();
}

void Node::SetScale(float3 scale) {

	m_Scale = scale;
	BuildGeo();
	Updated();
}

void Node::Move(float3 delta) {

	m_Position = m_Position + (delta * m_Rotation);
	BuildGeo();
	Updated();
}

void Node::Translate(float3 delta) {

	m_Position = m_Position + delta;
	BuildGeo();
	Updated();

}

float3 Node::TransformVector(float3 vector) {

	return vector * m_Rotation;

}

void Node::Rotate(float pitch, float yaw, float roll) {


	yaw = MathsHelp::Deg2Rad(yaw);
	pitch = MathsHelp::Deg2Rad(pitch);
	roll = MathsHelp::Deg2Rad(roll);
	
	Updated();

}

void RotationMatrixToEulerAngles2(const float4x4& rotationMatrix, float& pitch, float& yaw, float& roll)
{
	yaw = std::atan2(rotationMatrix[0][2], rotationMatrix[2][2]);
	pitch = std::asin(-rotationMatrix[1][2]);
	roll = std::atan2(rotationMatrix[1][0], rotationMatrix[1][1]);

	// Convert radians to degrees and normalize
	pitch = MathsHelp::Rad2Deg(pitch);
	yaw = MathsHelp::Rad2Deg(yaw);
	roll = MathsHelp::Rad2Deg(roll);

}

float3 Node::GetRotationEU() {

	float x, y, z;
	 RotationMatrixToEulerAngles2(m_Rotation, x, y, z);
	 return float3(x, y, z);

	//float p, y, r;
//	RotationMatrixToEulerAngles(m_Rotation.Inverse() , p, y, r);
//	return float3(MathsHelp::Rad2Deg(p), MathsHelp::Rad2Deg(y), MathsHelp::Rad2Deg(r));

}

void Node::Turn(float pitch, float yaw, float roll,bool local) {

	yaw = MathsHelp::Deg2Rad(yaw);
	pitch = MathsHelp::Deg2Rad(pitch);
	roll = MathsHelp::Deg2Rad(roll);


	float4x4 turn = float4x4::RotationX(pitch) * float4x4::RotationY(yaw) * float4x4::RotationZ(roll);

	if (local) {
		m_Rotation = turn * m_Rotation;
		
	}
	else {

		m_Rotation = m_Rotation * turn;

	}
	BuildGeo();
	Updated();
}

float4x4 Node::GetWorldMatrix() {

	float4x4 translationMatrix = float4x4::Translation(m_Position);
	float4x4 rotationMatrix = m_Rotation;
	float4x4 scaleMatrix = float4x4::Scale(m_Scale);

	// Combine the transformation matrices in the correct order (scale * rotation * translation)
	float4x4 worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	return worldMatrix;

}

void Node::Update() {

	//Turn(0, 0.1f, 0, false);

	if (m_IsPlaying) {
		for (auto gs : m_Scripts) {

			auto up_func = gs->FindFunction("Update");
			up_func->Call(nullptr);

		}
	}


	for (auto n : m_Nodes) {

		n->Update();

	}

}

void Node::AddScript(std::string path) {


	auto name = FileHelp::GetFileName(path);

	Engine::m_ScriptHost->LoadModule(path);

	auto test_i = Engine::m_ScriptHost->CreateInstance(name);

	m_Scripts.push_back(test_i);


	//m_NodeClass = Engine::m_ScriptHost->CreateInstance("Node");


	VVar* node_v = test_i->FindVar("node");

	m_NodeClass = node_v->GetClassValue();
	auto obj = m_NodeClass->FindVar("C");



	//auto f1 = m_NodeClass->FindFunction("Node");

	//f1->Call(nullptr);


	//auto obj = m_NodeClass->FindVar("C");
//	auto pos = m_NodeClass->FindVar("Position");
//	auto scale = m_NodeClass->FindVar("Scale");
//	auto rot = m_NodeClass->FindVar("Rotation");
//
//	auto p_c = pos->GetClassValue()->FindVar("C");
//	auto s_c = scale->GetClassValue()->FindVar("C");
//	auto r_c = rot->GetClassValue()->FindVar("C");

//	p_c->SetC(&m_Position);
//	s_c->SetC(&m_Scale);
//	rot->SetC(&m_Rotation);

	obj->SetC((void*)this);




}

void Node::BeginPlay() {

	Push();


	m_IsPlaying = true;
	for (auto node : m_Nodes)
	{
		node->BeginPlay();
	}

}

void Node::Stop() {
	Pop();
	
	m_IsPlaying = false;

	for (auto node : m_Nodes) {
		node->Stop();
	}

}

void Node::Push() {
	m_PushedPosition = m_Position;
	m_PushedRotation = m_Rotation;
	m_PushedScale = m_Scale;
}

void Node::Pop() {
	m_Position = m_PushedPosition;
	m_Rotation = m_PushedRotation;
	m_Scale = m_PushedScale;

}

void Node::SetStatic(bool stat) {

	m_Static = stat;
	
}

bool Node::GetStatic() {

	return m_Static;

}

std::vector<VClass*> Node::GetScripts() {

	return m_Scripts;

}

std::string Node::GetFullName() {

	std::string root = "";

	if (m_Root != nullptr) {

		root = m_Root->GetFullName();
	}

	if (root != "")
	{
		return root + "." + m_Name;
	}
	return m_Name;

}

void Node::SetRoot(Node* node) {

	m_Root = node;

}

void Node::SetResourcePath(std::string path) {

	m_ResourcePath = path;

}

std::string Node::GetResourcePath() {

	return m_ResourcePath;

}

void Node::WriteNode(VFile* file) {

	file->WriteInt(1);
	file->WriteVec3(m_Position);
	file->WriteMatrix(m_Rotation);
	file->WriteVec3(m_Scale);
	file->WriteString(m_Name.c_str());

	file->WriteInt(m_Nodes.size());

	for (auto node : m_Nodes) {

		node->WriteNode(file);

	}


}

void Node::ReadNode(VFile* file) {

	m_Position = file->ReadVec3();
	m_Rotation = file->ReadMatrix();
	m_Scale = file->ReadVec3();
	m_Name = file->ReadString();

}

void Node::RenderChildrenForcedMaterial(MaterialBase* material) {
	for (auto node : m_Nodes) {
		node->RenderForcedMaterial(material);
	}
}

void Node::RenderForcedMaterial(MaterialBase* material)
{
	RenderChildrenForcedMaterial(material);
}