#pragma once
#include "VToken.h"
#include <vector>
#include <string>
#include "VName.h"
#include "VAction.h"

class VExpression;

class VVarGroup : public VAction
{
public:

	VVarGroup(TokenType type);
	std::vector<VName> GetNames() {
		return m_Names;
	}
	std::vector<VExpression*> GetExpressions() {
		return m_Defaults;
	}
	void AddName(VName name,VExpression* expr);
	TokenType GetType() {
		return m_Type;
	}
private:

	TokenType m_Type;
	std::vector<VName> m_Names;
	std::vector<VExpression*> m_Defaults;

};

