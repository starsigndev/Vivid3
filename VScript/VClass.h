#pragma once
#include <vector>
#include <string>
#include "VName.h"
#include "VVarGroup.h"

class VFunction;

class VClass
{
public:

	void SetName(VName name);
	void AddVarGroup(VVarGroup* group);
	void AddFunction(VFunction* func);
	VFunction* FindFunction(VName name);

private:

	VName m_Name;
	std::vector<VVarGroup*> m_Groups;
	std::vector<VFunction*> m_Funcs;

};

