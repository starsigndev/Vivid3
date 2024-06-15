#pragma once
#include "BasicMath.hpp"
using namespace Diligent;


class Material2D;
class Texture2D;

class Draw2D
{
public:

	Draw2D();
	void Rect(Texture2D* image, float2 position, float2 size, float4 color);


private:

	Material2D* m_Material;

};
