#include "pch.h"
#include "CubeRenderer.h"
#include "SceneGraph.h"
#include "RenderTargetCube.h"
#include "NodeCamera.h"
#include "Node.h"
#include <math.h>

CubeRenderer::CubeRenderer(SceneGraph* graph, RenderTargetCube* target)
{

	m_Graph = graph;
	m_Target = target;

}

void CubeRenderer::RenderDepth(float3 pos, float maxZ) {

	auto prev_cam = m_Graph->GetCamera();
	auto new_cam = new NodeCamera;
	m_Graph->SetCamera(new_cam);
	new_cam->SetPosition(pos);
	new_cam->SetNearZ(prev_cam->GetNearZ());
	new_cam->SetFarZ(maxZ);
	new_cam->SetFov(90.0f);
	for (int i = 0; i < 6; i++) {

		switch (i) {
		case 0:
			new_cam->SetRotation(float4x4::RotationY(PI_F / 2.0f));
			break;
		case 1:
			new_cam->SetRotation(float4x4::RotationY(-PI_F / 2.0f));
			break;
		case 2:
			new_cam->SetRotation(float4x4::RotationX(-PI_F / 2.0f));
			break;
		case 3:
			new_cam->SetRotation(float4x4::RotationX(PI_F / 2.0f));
			break;
		case 4:
			new_cam->SetRotation(float4x4::Identity());
			break;
		case 5:
			new_cam->SetRotation(float4x4::RotationY(PI_F));
			break;
		}

		m_Target->Bind(i);
		m_Graph->RenderDepth();
		m_Target->Release(i);
		

	}

	m_Graph->SetCamera(prev_cam);

}