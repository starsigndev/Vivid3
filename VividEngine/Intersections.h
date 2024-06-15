#pragma once
#include "CLBase.h"
#include "BasicMath.hpp"

using namespace Diligent;

class Mesh3D;

struct CastResult {

	float Distance = 0.0;
	bool Hit = false;

};

class Intersections : public CLBase
{
public:

	Intersections();
	CastResult CastMesh(float3 pos, float3 dir, Mesh3D* mesh);

private:

};

