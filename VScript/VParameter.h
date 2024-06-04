#pragma once
#include "VToken.h"
#include "VName.h"

class VExpression;

class VParameter
{
public:

	VParameter();
	void SetName(VName name);
	void SetDefaultExpression(VExpression* expr);
	void SetType(TokenType type);

private:

	TokenType m_Type;
	VName m_Name;
	VExpression* m_Default;


};

