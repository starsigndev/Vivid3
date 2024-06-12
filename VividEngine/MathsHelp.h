#pragma once
#include <cmath> // For M_PI constant
#include "BasicMath.hpp"

using namespace Diligent;
constexpr double MPI = 3.14159265358979323846;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class MathsHelp
{
public:

	static float Deg2Rad(float deg) {
		return deg * (float)MPI / 180.0;
	}
	static float Rad2Deg(float r)
	{
		float degrees = r * (180.0f / static_cast<float>(M_PI));
		// Normalize degrees to be within 0 to 360
	
		return degrees;
	}

	static float Distance(float3 v1, float3 v2);

};

