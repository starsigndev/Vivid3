#pragma once
#include <vector>
#include "VClass.h"
#include "VVar.h"

class VExpression;

struct ExpElement {

	float FloatValue = 0;
	float IntValue = 0;
	std::string StringValue = "";
	VClass* ClassValue = nullptr;
	VVar* VarElement;
	TokenType EleType;
	VName VarName;

};

class VExpression
{
public:

	std::vector<ExpElement> Elements;
	VContext* m_Context;

	VVar* Express();
};

