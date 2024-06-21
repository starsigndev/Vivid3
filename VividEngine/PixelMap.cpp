#include "pch.h"
#include "PixelMap.h"

PixelMap::PixelMap(int w, int h) {

	m_Width = w;
	m_Height = h;
	m_Data = new float[w * h * 4];
	m_BPP = 4;
	for (int l = 0; l < (w * h * 4); l++) {
		
		m_Data[l] = 0.0f;

		//auto pix = (unsigned char*)(m_Data) + l;
		//pix[0] = 0;


	}

}

float4 PixelMap::GetColor(int x, int y) {

	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) return float4(0, 0, 0, 0);
	float4 res;

	int loc = (y * m_Width * m_BPP) + (x * m_BPP);
	res.x = m_Data[loc++];
	res.y = m_Data[loc++];
	res.z = m_Data[loc++];
	res.w = m_Data[loc++];

	return res;




}

void PixelMap::SetColor(int x, int y, float4 col) {

	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) return;
	float4 res;

	int loc = (y * m_Width * m_BPP) + (x * m_BPP);
	m_Data[loc++] = col.x;
	m_Data[loc++] = col.y;
	m_Data[loc++] = col.z;
	m_Data[loc++] = col.w;

}