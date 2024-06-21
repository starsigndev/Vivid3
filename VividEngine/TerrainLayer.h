#pragma once

class Texture2D;
class TextureCube;
class MaterialMeshPBR;
class PixelMap;

class TerrainLayer
{
public:

	TerrainLayer();
	void PlotBrush(float x, float y, int w, int h, float strength);
	void SetLayerMap(Texture2D* tex) {
		m_LayerMap = tex;
	}
	void SetPixels(PixelMap* pixels) {
		m_LayerPixMap = pixels;
	}
	Texture2D* GetLayerMap() {
		return m_LayerMap;
	}
	PixelMap* GetPixels() {
		return m_LayerPixMap;
	}
	Texture2D* GetColor() {
		return m_Color;
	}
	void SetColor(Texture2D* color) {
		m_Color = color;
	}
private:

	Texture2D* m_Color;
	MaterialMeshPBR* m_Material;
	Texture2D* m_LayerMap;
	PixelMap* m_LayerPixMap;


};

