#include "pch.h"
#include "VParser.h"
#include "VClass.h"
#include "VVarGroup.h"
#include "VFunction.h"
#include "VDefineParams.h"
#include "VCodeBody.h"
#include "VStatementCall.h"
#include "VCallParameters.h"
#include "VExpression.h"
#include "VVarAssign.h"
#include "VClassAssign.h"

VParser::VParser() {

}

VModule* VParser::ParseModule(VTokenStream stream) {

	m_Stream = stream;

	VModule* module = new VModule;

	auto token = m_Stream.GetNext();

	Assert(token.GetType() == T_Module, "Expected 'module' keyword.");

	auto name = ParseName();

	module->SetName(name);


	while (!m_Stream.End()) {

		auto token = m_Stream.GetNext();

		switch (token.GetType()) {
		case T_Class:
		{
			auto p_class = ParseClass();
			int aa = 1;
			module->AddClass(p_class);

		}
			break;
		default:
			Err("Unexpected token in module:" + token.GetLex());
			break;
		}

		int b = 5;

	}

	return module;

}

VName VParser::ParseName() {

	std::vector<std::string> names;

	while (true) {

		auto tok = m_Stream.GetNext();
		if (tok.GetType() == T_Ident) {
			names.push_back(tok.GetLex());
			if (m_Stream.Peek(0).GetType() == T_Access)
			{
				m_Stream.GetNext();
				continue;
			}
			else {
//				m_Stream.Back();
				break;
			}
		}
		else {
			m_Stream.Back();
			break;
		}

	}

	return VName(names);

}

VClass* VParser::ParseClass() {

	auto name = ParseName();

	auto n_cls = new VClass;

	n_cls->SetName(name);

	if (m_Stream.GetNext().GetType() == T_End) {

		//m_Stream.Back();
		return n_cls;

	}
	else {

		m_Stream.Back();

	}

	while (!m_Stream.End()) {

		auto token = m_Stream.GetNext();

		switch (token.GetType()) {
		case T_Func:
		{
			int bb = 5;
			VFunction* func = ParseFunction();
			n_cls->AddFunction(func);
		}
			break;
		case T_End:

			return n_cls;

			break;
		case T_Int:
		case T_Float:
		case T_String:
		case T_Bool:

			VVarGroup* group = new VVarGroup(token.GetType());
			n_cls->AddVarGroup(group);


			while (!m_Stream.End()) {

				auto peek = m_Stream.Peek(0);

				if (peek.GetLex() == ",")
				{
					m_Stream.GetNext();
					continue;
				}
				if (peek.GetType() == T_EOL) {

					//n_cls->AddVars(
					//)
					m_Stream.GetNext();
					break;

				}
				auto v_name = ParseName();
			
				auto next = m_Stream.Peek(0);

				VExpression* expr = nullptr;

				if (next.GetLex() == "=")
				{
					expr = ParseExpression();

					auto tok = m_Stream.Peek(0);
				}

				group->AddName(v_name,expr);

			}

			break;
		}

		int a = 5;

	}

	m_Stream.Back();

	return n_cls;

	
}

VFunction* VParser::ParseFunction() {

	//auto token = m_Stream.GetNext();

	auto name = ParseName();

	VFunction* func = new VFunction;
	func->SetName(name);

	auto next = m_Stream.GetNext();

	if (next.GetLex() == "(")
	{
		auto next = m_Stream.GetNext();

		if (next.GetType() == T_End)
		{
			return func;
		}

		if (next.GetLex() == ")") {
			m_Stream.Back();
			auto body = ParseCodeBody();
			func->SetBody(body);
			auto nx = m_Stream.Peek(0);
			if (nx.GetType() == T_End)
			{
				m_Stream.GetNext();
			}
			return func;
		}
		m_Stream.Back();
		auto pars = ParseParameters();

		func->SetParams(pars);
		m_Stream.Back();
		auto body = ParseCodeBody();
		func->SetBody(body);
		auto nx = m_Stream.Peek(0);
		if (nx.GetType() == T_End)
		{
			m_Stream.GetNext();
		}

		return func;
	}
	else {

		auto pars = ParseParameters();

		func->SetParams(pars);
		int aa = 5;

		auto next = m_Stream.GetNext();
		if (next.GetType() == T_End)
		{
			return func;
		}

	}

	int a = 5;

	return nullptr;
}

PredictType VParser::PredictNext(VTokenStream stream)
{

	bool p_statement = false;
	int idents = 0;

	if (m_Stream.Match({ TokenType::T_Ident,TokenType::T_Ident }))
	{
		return P_DeclareObject;
	}
	if (m_Stream.Match({ TokenType::T_Ident,TokenType::T_LeftPara }))
	{
		return P_Statement;
	}

	if (m_Stream.Match({ TokenType::T_Ident,TokenType::T_Access }))
	{
		if (m_Stream.LineHas("="))
		{
			return P_ClassAssign;
		}
		else {
			return P_ClassCall;
		}
	}

	//if(m_Stream.Match({TokenType::T_Access}))


	while (!stream.End()) {

		auto tok = stream.GetNext();

		switch (tok.GetType()) {
		case T_Int:
		case T_Float:
		case T_Bool:
		case T_String:
		

			return P_DeclareVar;

			break;
		case T_Ident:
		//	p_statement = true;
			idents++;
			if (idents == 1) {

				//if (m_Stream.Peek(0).GetType() == TokenType::T_Ident)
				{
				//	return P_DeclareObject;
				}

			}





			break;
		default:
			if (tok.GetLex() == "(" || tok.GetLex() == "()")
			{
				return P_Statement;
			}
			if (tok.GetLex() == "end")
			{
				return P_End;
			}
			break;
		}

	}

	return P_Unknown;

}

VVarGroup* VParser::ParseDeclareObject() {

	auto tok = m_Stream.GetNext();

	VVarGroup* vg = new VVarGroup(TokenType::T_Class);
	vg->SetClassType(tok.GetLex());

	while (!m_Stream.End()) {

		auto tok = m_Stream.GetNext();
		if (tok.GetLex() == ",")
		{
			continue;
		}
		if (tok.GetLex() == ";")
		{
			return vg;
		}
		auto name = VName();
		name.Add(tok.GetLex());
		
		VExpression* def = nullptr;

		//auto test = m_Stream.Peek(0);
		if (m_Stream.Peek(0).GetLex()=="=") {

			def = ParseExpression();
			

			int b = 5;


		}

		vg->AddName(name,def);


		int b = 5;

	}


	int b = 5;

	return vg;

}

VClassAssign* VParser::ParseClassAssign() {

	//auto tok = m_Stream.GetNext();
	auto name = ParseName();

	VClassAssign* ass = new VClassAssign;

	ass->SetName(name);

	auto tok = m_Stream.Peek(0);
	if (tok.GetLex() == "=")
	{
		m_Stream.GetNext();
	}

	auto exp = ParseExpression();

	ass->SetExpression(exp);

	return ass;

}

VCodeBody* VParser::ParseCodeBody() {

	//auto token = m_Stream.GetNext();
	auto tok = m_Stream.Peek(0);
	if (tok.GetLex() == ")")
	{
		m_Stream.GetNext();
	}
	int ba = 5;
	VCodeBody* body = new VCodeBody;

	while (!m_Stream.End()) {

		PredictType pt = PredictNext(m_Stream);

		switch (pt) {
		case P_ClassAssign:

		{
			auto cls_assign = ParseClassAssign();
			body->AddCode(cls_assign);
		}
			break;
		case P_DeclareObject:
		{
			auto declare = ParseDeclareObject();
			body->AddCode(declare);

		}
			break;
		case P_Assign:
		{
			auto ass = ParseAssign();
			body->AddCode(ass);
		}
			break;
		case P_New:

		

			break;
		case P_DeclareVar:
		{
			//auto tok = m_Stream.GetNext();
			auto declare = ParseDeclare();
			body->AddCode(declare);
			int b = 5;
		}
			break;
		case P_Statement:

		{
			//	m_Stream.Back();
			auto statement = ParseStatement();
			body->AddCode(statement);
		}
			break;
		case P_End:

			return body;

			break;
		}


		int a = 5;

	}
	int b = 5;

	return nullptr;
}

VVarAssign* VParser::ParseAssign() {

	auto name = ParseName();

	if (!m_Stream.Peek(0).GetType() == T_Equal)
	{

		Err("Expecting '='\n");

	}

	VVarAssign* ass = new VVarAssign;

	ass->SetExpression(ParseExpression());
	ass->SetTarget(name);

//	ass
	auto tok = m_Stream.GetNext();

	int aa = 5;



	return ass;

}

VVarGroup* VParser::ParseDeclare() {

	VVarGroup* group = new VVarGroup(m_Stream.GetNext().GetType());

	while (!m_Stream.End()) {

		auto tok = m_Stream.GetNext();
		if (tok.GetLex() == ",")
		{
			continue;
		}
		if (tok.GetLex() == ";")
		{
			return group;
		}
		auto name = VName();
		name.Add(tok.GetLex());
		group->AddName(name, nullptr);
		int b = 5;

	}

	return group;

}

VStatementCall* VParser::ParseStatement() {

	auto tok = m_Stream.GetNext();
	if (tok.GetLex() == ";")
	{
		tok = m_Stream.GetNext();
	}

	VStatementCall* call = new VStatementCall;
	call->SetName(tok.GetLex());

	tok = m_Stream.GetNext();
	auto tok2 = m_Stream.Peek(0);

	if (tok.GetLex() == "(" && tok2.GetLex() == ")") {

	//	m_Stream.GetNext();
		//call->SetName(m_Stream.GetNext().GetLex());

		auto el = m_Stream.Peek(0);
		if (el.GetLex() == ")")
		{
			el = m_Stream.Peek(1);
		}

		if (el.GetType() == T_EOL)
		{
			m_Stream.GetNext();
			m_Stream.GetNext();
			return call;
		}
		else {
			Err("Unknown follow up to statement call.\n");
		}

	}
	else {

	//	tok2 = m_Stream.GetNext();

		auto call_params = ParseCallParameters();

		call->SetCallParameters(call_params);
		return call;

		//int aa = 5;

	}

	int a = 5;

	return nullptr;

}

VCallParameters* VParser::ParseCallParameters() {

	VCallParameters* params = new VCallParameters;
	//auto tok = m_Stream.GetNext();
	while (!m_Stream.End()) {

		auto token = m_Stream.Peek(0);

		if (token.GetLex() == ")" || token.GetLex() == ";")
		{
			if (token.GetLex() == ";")
			{
				int aa = 5;
				m_Stream.GetNext();
			}
			return params;
		}

		VExpression* expression = ParseExpression();

		params->AddParam(expression);



	}

	int b = 5;

	return nullptr;
}

VExpression* VParser::ParseExpression() {

	//auto toke = m_Stream.GetNext();
	if (m_Stream.Peek(0).GetLex() == "=") {
		m_Stream.GetNext();
	}

	VExpression* expr = new VExpression;

	VName v_name;

	while (!m_Stream.End()) {

		auto toke = m_Stream.GetNext();
		if (toke.GetLex() == ",")
		{
			return expr;
		}
		if (toke.GetLex() == ")")
		{
			return expr;
		}
		if (toke.GetLex() == ";")
		{
			m_Stream.Back();
			return expr;
		}
		if (toke.GetLex() == "(")
		{
			ExpElement sub_ele;
			sub_ele.IsSubExpr = true;
			sub_ele.SubExpr = ParseExpression();
			expr->Elements.push_back(sub_ele);
			continue;
		}

		if (toke.GetLex() == "new")
		{
			toke = m_Stream.GetNext();
			auto cls_type = toke.GetLex();
			int bb = 5;
			ExpElement new_ele;
			new_ele.ClassType = cls_type;
			new_ele.IsNew = true;
			m_Stream.GetNext();
			new_ele.NewParams = ParseCallParameters();
			m_Stream.Back();
			expr->Elements.push_back(new_ele);
			return expr;


		}

		switch (toke.GetType()) {
		case T_Operator:
		{
			ExpElement op_ele;
			op_ele.EleType = T_Operator;
			if (toke.GetLex() == "+")
			{
				op_ele.OpType = T_Plus;
			}
			if (toke.GetLex() == "-")
			{
				op_ele.OpType = T_Minus;
			}
			if (toke.GetLex() == "*")
			{
				op_ele.OpType = T_Times;
			}
			if (toke.GetLex() == "/")
			{
				op_ele.OpType = T_Divide;
			}
			if (toke.GetLex() == "=") {
				op_ele.OpType = T_Equal;
			}
			expr->Elements.push_back(op_ele);
		}

			break;
		case T_Ident:
		{

			ExpElement var_ele;

			m_Stream.Back();

			VName qname = ParseName();
			//qname.Add(toke.GetLex());
			var_ele.VarName = qname;


			var_ele.EleType = T_Ident;
			expr->Elements.push_back(var_ele);


		}
			break;
		case T_Number:
		{
			ExpElement num_ele;

			num_ele.EleType = T_Number;
			num_ele.IntValue = std::stoi(toke.GetLex());

			expr->Elements.push_back(num_ele);

		}

			break;
		case T_FloatNumber:
		{
			ExpElement num_ele;

			num_ele.FloatValue = std::stof(toke.GetLex());
			num_ele.EleType = T_FloatNumber;

			expr->Elements.push_back(num_ele);
		}
			break;
		default:

			if (toke.GetLex() == ")")
			{
			
			
					return expr;
			
			}
			if (toke.GetLex() == ";")
			{
				m_Stream.Back();
				return expr;
			}

			break;
		}

		int b = 5;

	}

	return nullptr;
}

VDefineParams* VParser::ParseParameters() {

	VDefineParams* params = new VDefineParams;

	while (!m_Stream.End()) {
	
		auto token = m_Stream.GetNext();
		if (token.GetLex() == ",")
		{
			continue;
		}
		if (token.GetLex() == ")")
		{
			return params;
		}
		auto name = ParseName();
		VParameter* new_param = new VParameter;
		if (m_Stream.Peek(0).GetLex() == "=")
		{

		}

	
		new_param->SetType(token.GetType());
		new_param->SetName(name);


		params->AddParam(new_param);

	}
	int b = 5;

	return nullptr;

}

void VParser::Err(std::string msg) {

	printf("Error parsing.\n");
	printf(msg.c_str());
	printf("\n");

}

void VParser::Assert(bool value, std::string msg)
{
	if (!value) {
		Err(msg);
		exit(0);
	}
}