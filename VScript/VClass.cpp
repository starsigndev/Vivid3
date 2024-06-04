#include "pch.h"
#include "VClass.h"
#include "VFunction.h"

void VClass::SetName(VName name) {

	m_Name = name;

}

void VClass::AddVarGroup(VVarGroup* group) {

	m_Groups.push_back(group);

}

void VClass::AddFunction(VFunction* func)
{

	m_Funcs.push_back(func);

}

VFunction* VClass::FindFunction(VName name) {

	for (auto func : m_Funcs) {

		if (func->GetName().SameName(name)) {
			return func;
		}

	}
	return nullptr;

}