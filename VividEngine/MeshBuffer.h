#pragma once

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "BasicMath.hpp"

using namespace Diligent;

class Mesh3D;

class MeshBuffer
{
public:

	MeshBuffer();
	void SetMesh(Mesh3D* mesh);
	void Build();

private:
	RefCntAutoPtr<IBuffer> VertexBuffer;
	RefCntAutoPtr<IBuffer> IndexBuffer;
	Mesh3D* m_Mesh;
};

