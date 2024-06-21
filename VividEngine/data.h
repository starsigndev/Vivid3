#pragma once
#include "BasicMath.hpp"

using namespace Diligent;

struct Vertex {

	float3 position;
	float4 color;
	float3 texture;
	float3 normal;
	float3 binormal;
	float3 tangent;
	float4 bone_ids;
	float4 bone_weights;

};

struct Triangle
{

	Uint32 v0=0, v1=0, v2=0;

};

struct TerrainVertex {

	float3 position;
	float4 color;
	float3 texture;
	float3 normal;
	float3 binormal;
	float3 tangent;
	float3 layercoord;

};