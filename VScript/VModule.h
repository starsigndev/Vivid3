#pragma once
#include "VName.h"
#include "VClass.h"

class VModule
{
public:
	VModule();
	void SetName(VName name);
	void AddClass(VClass* cls);
	VName GetName();
private:

	VName m_Name;
	std::vector<VClass*> m_Classes;
};

