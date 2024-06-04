#pragma once
#include "VToken.h"
#include <vector>
#include <string>
#include "VName.h"

class VExpression;

class VVarGroup
{
public:

	VVarGroup(TokenType type);
	void AddName(VName name,VExpression* expr);

private:

	TokenType m_Type;
	std::vector<VName> m_Names;
	std::vector<VExpression*> m_Defaults;

};

