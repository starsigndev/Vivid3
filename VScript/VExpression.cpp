#include "pch.h"
#include "VExpression.h"
#include "VContext.h"

VVar* VExpression::Express() {

	auto v = new VVar;

	if (Elements[0].VarName.GetNames().size() > 0)
	{
		v->m_IntValue = 0;
		auto fv = m_Context->FindVar(Elements[0].VarName.GetNames()[0]);
		v->m_IntValue = fv->m_IntValue;
		return v;

	}
	v->m_IntValue = Elements[0].IntValue;

	return v;
}