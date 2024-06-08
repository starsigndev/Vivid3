#pragma once
#include "VToken.h"
#include <vector>
#include <string>
#include "VName.h"
#include "VAction.h"

class VExpression;
class VLambda;

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
	void SetClassType(std::string type) {
		m_ClassType = type;
	}
	std::string GetClassType() {
		return m_ClassType;
	}
	VVar* Exec();
	VLambda* GetLambda() {
		return m_Lambda;
	}
	void SetLambda(VLambda* lam)
	{
		m_Lambda = lam;
	}

private:

	TokenType m_Type;
	std::vector<VName> m_Names;
	std::vector<VExpression*> m_Defaults;
	std::string m_ClassType = "";
	VLambda* m_Lambda;

};

