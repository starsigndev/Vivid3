#include "pch.h"
#include "VClass.h"
#include "VFunction.h"
#include "VScope.h"
#include "VVar.h"
#include "VName.h"
#include "VExpression.h"
#include "VDefineParams.h"
#include "VParameter.h"
#include "VContext.h"
#include "VScope.h"

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
	m_InstanceScope->NoRoot();

	for (auto g : m_Groups) {

		int ii = 0;
		if (g->GetType() != T_Ident) {
			for (auto v : g->GetNames())
			{
				auto nv = new VVar;

				nv->SetName(v.GetNames()[0]);

				//nv->m_Name = v.GetNames()[0];

				if (g->GetExpressions()[ii] != nullptr) {
					g->GetExpressions()[ii]->m_Context = this->m_Context;
					auto res = g->GetExpressions()[ii]->Express();

					switch (g->GetType()) {
					case T_Number:
						nv->SetInt(res->ToInt());
						//nv->m_IntValue = res->ToInt();
						break;
					case T_Float:
						nv->SetFloat(res->ToFloat());
						//nv->m_FloatValue = res->ToFloat();
						break;
					}

				}
				//nv->m_Type = g->GetType();

				nv->SetType(g->GetType());
				m_InstanceScope->RegisterVar(nv);
				ii++;

				//nv->m_IntValue = 
			}
		}
		else {
			for (auto v : g->GetNames())
			{
				auto nv = new VVar;
				//nv->m_Name = v.GetNames()[0];

				nv->SetName(v.GetNames()[0]);

			//	if (g->GetExpressions()[ii] != nullptr) {
			//		g->GetExpressions()[ii]->m_Context = this->m_Context;
			//		nv->m_IntValue = g->GetExpressions()[ii]->Express()->m_IntValue;
			//	}

				nv->SetType(T_Class);
				nv->SetClassType(g->GetClassType());

				//nv->m_Type = T_Class;
				//nv->m_ClassType = g->GetClassType();
				if (g->GetExpressions()[ii] != nullptr) {
					g->GetExpressions()[ii]->m_Context = this->m_Context;
					nv->SetClassValue(g->GetExpressions()[ii]->Express()->GetClassValue());

				}
				m_InstanceScope->RegisterVar(nv);

				ii++;

				//nv->m_IntValue = 
			}
		}

	}

	m_InstanceScope->SetClass(this);
	m_InstanceScope->NoRoot();

}

VVar* VClass::FindVar(std::string name) {

	for (auto v : m_InstanceScope->GetVars()) {
		if (v->IsName(name)) {
			return v;
		}
	}
	return nullptr;
}

VFunction* VClass::FindFunctionBySig(std::string name,std::vector<TokenType> sig) {

	
	for (auto func : m_Funcs) {

		if (func->GetName().GetNames()[0] == name)
		{

			if (sig.size() == 0 && func->GetParams() == nullptr) {
				return func;
			}
			auto params = func->GetParams();
			auto pl = params->GetParams();

			int si = 0;
			for (auto p : pl) {

				if (p->GetType() == T_Int)
				{
					if (sig[si] == T_Number)
					{

					}
					else {
						return nullptr;
					}
				}

			}
			
			return func;
			int b = 5;
			//		return func;
		}

	}
	return nullptr;
}