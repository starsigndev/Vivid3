#include "pch.h"
#include "VVarGroup.h"
#include "VContext.h"
#include "VName.h"

VVarGroup::VVarGroup(TokenType type) {

	m_Type = type;

}

void VVarGroup::AddName(VName name,VExpression* expr) {

	m_Names.push_back(name);
	m_Defaults.push_back(expr);

}

VVar* VVarGroup::Exec() {

	//int a = 5;
	auto con = GetContext();

	auto top_scope = con->GetTopScope();

	int idx = 0;
	for (auto name : m_Names) {
		VVar* nv = new VVar;
		nv->m_Type = TokenType::T_Class;
		nv->m_Type = m_Type;
		nv->m_ClassType = m_ClassType;
		nv->m_Name = name.GetNames()[0];
		auto def = m_Defaults[idx];

		if (def != nullptr) {

			def->m_Context = GetContext();
			VVar* res = def->Express();
			nv->m_ClsValue = res->m_ClsValue;
			nv->m_IntValue = res->m_IntValue;
			nv->m_FloatValue = res->m_FloatValue;
			nv->m_ClassType = res->m_ClassType;
			if (nv->m_ClsValue != nullptr) {
				nv->m_Type = TokenType::T_Class;
			}


		}

		top_scope->RegisterVar(nv);

		idx++;
	}

	int a = 5;

	return nullptr;
}