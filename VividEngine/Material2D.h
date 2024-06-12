#pragma once
#include "MaterialBase.h"
class Material2D :
    public MaterialBase
{
public:

    Material2D();
    void Create();
    void Bind(Texture2D* tex);

private:
};

