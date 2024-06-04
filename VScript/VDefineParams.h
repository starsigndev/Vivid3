#pragma once
#include "VVarGroup.h"
#include <vector>
#include "VParameter.h"

class VDefineParams
{
public:

	void AddParam(VParameter* param);

private:

	std::vector<VParameter*> m_Pars;

};

