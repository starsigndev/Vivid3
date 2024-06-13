#pragma once
#include "VToken.h"
#include "VTokenStream.h"
#include "VModule.h"


enum PredictType {
	P_Statement, P_ClassCall,P_Unknown,P_End,P_DeclareVar,P_New,P_Assign,P_DeclareObject,P_ClassAssign,P_Return,
	P_DeclareArray,P_AssignArray,P_If,P_While,P_For,P_Lambda,P_Invoke,P_ForEach

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
class VClassAssign;
class VClassCall;
class VReturn;
class VDeclareArray;
class VAssignArray;
class VIf;
class VWhile;
class VFor;
class VLambda;
class VInvoke;
class VForEach;

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
	VVarGroup* ParseDeclareObject();
	VCallParameters* ParseCallParameters();
	VExpression* ParseExpression();
	VVarAssign* ParseAssign();
	VClassAssign* ParseClassAssign();
	VClassCall* ParseClassCall();
	VReturn* ParseReturn();
	VDeclareArray* ParseDeclareArray();
	VAssignArray* ParseAssignArray();
	VIf* ParseIf();
	VWhile* ParseWhile();
	VFor* ParseFor();
	VLambda* ParseLambda();
	VInvoke* ParseInvoke();
	VForEach* ParseForEach();

private:

	VTokenStream m_Stream;

};

