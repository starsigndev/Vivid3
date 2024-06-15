#pragma once
#include <cmath> // For M_PI constant
#include "BasicMath.hpp"

using namespace Diligent;
constexpr double MPI = 3.14159265358979323846;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <random>
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


	static bool IsPositionInsideBounds(float3 centre, float3 size, float3 position) {
		// Compute half extents
		float3 halfSize = size / 2.0f;

		// Calculate the min and max bounds of the box
		float3 minBounds = centre - halfSize;
		float3 maxBounds = centre + halfSize;

		// Check if the position is within the bounds
		return (position.x >= minBounds.x && position.x <= maxBounds.x &&
			position.y >= minBounds.y && position.y <= maxBounds.y &&
			position.z >= minBounds.z && position.z <= maxBounds.z);
	}
	static float4 getRandomFloat4(float min, float max) {
		// Use random device and mt19937 for random number generation
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(min, max);

		// Generate random components for float4
		float4 randomValue;
		randomValue.x = dis(gen);
		randomValue.y = dis(gen);
		randomValue.z = dis(gen);
		randomValue.w = dis(gen);

		return randomValue;
	}
};

