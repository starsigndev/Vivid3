#pragma once
#include "MaterialBase.h"

class Texture2D;

class MaterialTerrain :
    public MaterialBase
{
public:

    MaterialTerrain();
    void Create();
    void Bind(bool sp);
    void SetLayerMap(Texture2D* layer);

private:

    Texture2D* m_LayerMap = nullptr;

};

