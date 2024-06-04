#include "pch.h"
#include "VModule.h"

VModule::VModule() {


}

void VModule::SetName(VName name) {

	m_Name = name;

}

void VModule::AddClass(VClass* cls) {

	m_Classes.push_back(cls);

}

VName VModule::GetName() {

	return m_Name;

}