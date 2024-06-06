#pragma once
#include <vector>
#include "VClass.h"
#include "VVar.h"

class VExpression;
class VCallParameters;

struct ExpElement {

	float FloatValue = 0;
	float IntValue = 0;
	std::string StringValue = "";
	VClass* ClassValue = nullptr;
	VVar* VarElement;
	TokenType EleType;
	VName VarName;
	TokenType OpType;
	bool IsSubExpr = false;
	VExpression* SubExpr;
	std::string ClassType = "";
	bool IsNew = false;
	VCallParameters* NewParams;

};

class VExpression
{
public:

	std::vector<ExpElement> Elements;
	VContext* m_Context;
	bool Is_Float();
	bool Is_Int();
	std::vector<std::string> ToVector();
	VVar* Express();
};

