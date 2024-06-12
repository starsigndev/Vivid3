#pragma once
#include "BasicMath.hpp"

using namespace Diligent;
struct LineVertex {
	float3 position;
	float4 color;
};

class MeshLinesBuffer;
class MaterialMeshLines;

struct Line {
	int V0, V1;
};

class MeshLines
{
public:

	MeshLines();

	void AddVertex(LineVertex vertex) {
		m_Vertices.push_back(vertex);
	}

	void AddLine(Line line) {
		m_Lines.push_back(line);
	}

	std::vector<LineVertex> GetVertices();
	std::vector<Line> GetLines();

	void CreateBuffer();
	void Render();

private:


	std::vector<LineVertex> m_Vertices;
	std::vector<Line> m_Lines;
	MeshLinesBuffer* m_Buffer;
	MaterialMeshLines* m_Material;

};

