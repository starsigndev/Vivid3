#pragma once
#include "VToken.h"
#include "VTokenStream.h"
#include "VModule.h"


enum PredictType {
	P_Statement, P_ClassCall,P_Unknown,P_End,P_DeclareVar,P_New,P_Assign
};


class VStatementCall;
class VName;
class VClass;
class VFunction;
class VDefineParams;
class VCodeBody;
class VCallParameters;
class VExpression;
class VVarAssign;

class VParser
{
public:

	VParser();
	VModule* ParseModule(VTokenStream stream);
	void Err(std::string msg);
	void Assert(bool value, std::string msg);
	VName ParseName();
	VClass* ParseClass();
	VFunction* ParseFunction();
	VDefineParams* ParseParameters();
	VCodeBody* ParseCodeBody();
	PredictType PredictNext(VTokenStream stream);
	VStatementCall* ParseStatement();
	VVarGroup* ParseDeclare();
	VCallParameters* ParseCallParameters();
	VExpression* ParseExpression();
	VVarAssign* ParseAssign();

private:

	VTokenStream m_Stream;

};

