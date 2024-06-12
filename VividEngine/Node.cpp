#include "pch.h"
#include "Node.h"
#include "MathsHelp.h"
#ifndef M_PI_2

#define M_PI_2 1.57079632679489661923 // π/2

#endif

#include "BasicMath.hpp"

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


Node::Node() {

	m_Rotation = float4x4::Identity();
	m_Position = float3(0, 0, 0);
	m_Scale = float3(1, 1, 1);

}

void Node::AddNode(Node* node) {

	m_Nodes.push_back(node);

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

	m_Position = position;

}

float3 Node::GetPosition() {

	return m_Position;

}

void Node::SetRotation(float pitch, float yaw, float roll,bool edit) {

	yaw = MathsHelp::Deg2Rad(yaw);
	pitch = MathsHelp::Deg2Rad(pitch);
	roll = MathsHelp::Deg2Rad(roll);

	//m_Rotation = CreateRotationMatrix(pitch, yaw, roll);

	if (edit) {
		m_Rotation = float4x4::RotationY(yaw) * float4x4::RotationX(pitch) * float4x4::RotationZ(roll);
	}
	else {
		m_Rotation = float4x4::RotationX(pitch) * float4x4::RotationY(yaw) * float4x4::RotationZ(roll);
	}

}

void Node::SetScale(float3 scale) {

	m_Scale = scale;

}

void Node::Move(float3 delta) {

	m_Position = m_Position + (delta * m_Rotation);

}

void Node::Translate(float3 delta) {

	m_Position = m_Position + delta;

}

float3 Node::TransformVector(float3 vector) {

	return vector * m_Rotation;

}

void Node::Rotate(float pitch, float yaw, float roll) {


	yaw = MathsHelp::Deg2Rad(yaw);
	pitch = MathsHelp::Deg2Rad(pitch);
	roll = MathsHelp::Deg2Rad(roll);
	


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

}

float4x4 Node::GetWorldMatrix() {

	float4x4 translationMatrix = float4x4::Translation(m_Position);
	float4x4 rotationMatrix = m_Rotation;
	float4x4 scaleMatrix = float4x4::Scale(m_Scale);

	// Combine the transformation matrices in the correct order (scale * rotation * translation)
	float4x4 worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	return worldMatrix;

}