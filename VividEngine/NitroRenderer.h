#pragma once
#include "RendererBase.h"

//Nitro renderer is a non rtx renderer. 
class NitroRenderer : public RendererBase
{
public:

	void PreRender() override;
	void Render() override;

private:

};

