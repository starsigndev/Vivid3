#pragma once
#include <cmath> // For M_PI constant

constexpr double MPI = 3.14159265358979323846;


class MathsHelp
{
public:

	static float Deg2Rad(float deg) {
		return deg * (float)MPI / 180.0;
	}

};

