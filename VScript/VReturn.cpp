#include "pch.h"
#include "VExpression.h"
#include "VReturn.h"

void VReturn::SetExpression(VExpression* expression) {

	m_Expression = expression;

}

VExpression* VReturn::GetExpression() {

	return m_Expression;

}

VVar* VReturn::Exec() {

	m_Expression->m_Context = GetContext();
	return m_Expression->Express();

	//return nullptr;

}