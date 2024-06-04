#include "pch.h"
#include "VVarGroup.h"

VVarGroup::VVarGroup(TokenType type) {

	m_Type = type;

}

void VVarGroup::AddName(VName name,VExpression* expr) {

	m_Names.push_back(name);
	m_Defaults.push_back(expr);

}