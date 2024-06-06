#include "pch.h"
#include "VClassAssign.h"
#include "VVar.h"
#include "VContext.h"

void VClassAssign::SetName(VName name) {

	m_Name = name;

}

void VClassAssign::SetExpression(VExpression* expression) {

	m_Expression = expression;

}

VVar* VClassAssign::Exec() {

	int b = 5;

	auto final = GetContext()->FindVar(m_Name.GetNames());

//	auto cls = GetContext()->FindVar(m_Name.GetNames()[0]);
//	auto var = cls->m_ClsValue->FindVar(m_Name.GetNames()[1]);
	m_Expression->m_Context = GetContext();
	auto res = m_Expression->Express();
	final->m_IntValue = res->m_IntValue;
	final->m_FloatValue = res->m_FloatValue;
	final->m_ClsValue = res->m_ClsValue;
	final->m_ClassType = res->m_ClassType;

	return nullptr;
}