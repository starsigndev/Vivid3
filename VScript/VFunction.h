#pragma once
#include "VName.h"
#include <string>
#include <vector>
class VFunction
{
public:

	VFunction();
	void SetName(VName name);
	VName GetName();

private:

	VName m_Name;

};

