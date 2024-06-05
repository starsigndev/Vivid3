#include "pch.h"
#include "VClass.h"
#include "VFunction.h"
#include "VScope.h"
#include "VVar.h"
#include "VName.h"
#include "VExpression.h"

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

void VClass::SetContext(VContext* context) {

	m_Context = context;

	for (auto func : m_Funcs) {

		func->SetContext(context);

	}

}

VClass* VClass::Clone() {

	VClass* clone = new VClass;
	clone->SetName(m_Name);
	for (auto func : m_Funcs) {

		auto f2 = func->Clone();
		f2->SetOwner(clone);
		clone->AddFunction(f2);

	}

	for (auto g : m_Groups)
	{
		clone->AddVarGroup(g);
	}

	return clone;

}

VName VClass::GetName() {

	return m_Name;

}

VFunction* VClass::FindFunction(std::string name) {

	for (auto func : m_Funcs) {

		if (func->GetName().GetNames()[0] == name)
		{
			return func;
		}

	}

	return nullptr;

}

void VClass::CreateScope() {

	m_InstanceScope = new VScope;

	for (auto g : m_Groups) {

		int ii = 0;
		for (auto v : g->GetNames())
		{
			auto nv = new VVar;
			nv->m_Name = v.GetNames()[0];
			
			if (g->GetExpressions()[ii] != nullptr) {
				g->GetExpressions()[ii]->m_Context = this->m_Context;
				nv->m_IntValue = g->GetExpressions()[ii]->Express()->m_IntValue;
			}
			m_InstanceScope->RegisterVar(nv);
			ii++;

			//nv->m_IntValue = 
		}

	}

	m_InstanceScope->SetClass(this);
	m_InstanceScope->NoRoot();

}