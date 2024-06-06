#include "pch.h"
#include "VExpression.h"
#include "VContext.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "VFunction.h"
#include <stdexcept>
// INT EVAL
bool isOperator(const std::string& token) {
	return token == "+" || token == "-" || token == "*" || token == "/" ||
		token == "^" || token == "%" || token == "=";
}

// Helper function to get the precedence of an operator
// Helper function to get the precedence of an operator
int getPrecedence(const std::string& op) {
	if (op == "+" || op == "-") return 1;
	if (op == "*" || op == "/" || op == "%") return 2;
	if (op == "^") return 3;
	if (op == "=") return 0; // Equality check has the lowest precedence
	return -1;
}

float performOperationFLOAT(float a, float b, const std::string& op) {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") {
		if (b == 0) throw std::runtime_error("Division by zero");
		return a / b;
	}
	if (op == "%") {
		if (b == 0) throw std::runtime_error("Modulo by zero");
		return std::fmod(a, b);
	}
	if (op == "^") return std::pow(a, b);
	if (op == "=") return a == b ? 1 : 0;
	throw std::invalid_argument("Invalid operator");
}

// Helper function to perform an operation
int performOperationINT(int a, int b, const std::string& op) {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") {
		if (b == 0) throw std::runtime_error("Division by zero");
		return a / b;
	}
	if (op == "%") {
		if (b == 0) throw std::runtime_error("Modulo by zero");
		return a % b;
	}
	if (op == "^") return std::pow(a, b);
	if (op == "=") return a == b ? 1 : 0;
	throw std::invalid_argument("Invalid operator");
}


// Function to convert infix expression to postfix (RPN)
std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
	std::stack<std::string> operatorStack;
	std::vector<std::string> outputQueue;

	bool expectUnary = true; // True if we expect a unary operator or a number

	for (const std::string& token : tokens) {
		if (isOperator(token)) {
			if (expectUnary && token == "-") {
				outputQueue.push_back("0"); // Treat unary minus as subtraction from zero
			}
			while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(token)) {
				outputQueue.push_back(operatorStack.top());
				operatorStack.pop();
			}
			operatorStack.push(token);
			expectUnary = true;
		}
		else {
			outputQueue.push_back(token);
			expectUnary = false;
		}
	}

	while (!operatorStack.empty()) {
		outputQueue.push_back(operatorStack.top());
		operatorStack.pop();
	}

	return outputQueue;
}


// Function to evaluate an RPN expression
float evaluateFLOAT(const std::vector<std::string>& tokens) {
	std::stack<float> stack;

	for (const std::string& token : tokens) {
		if (isOperator(token)) {
			if (stack.size() < 2) throw std::runtime_error("Invalid expression");
			float b = stack.top();
			stack.pop();
			float a = stack.top();
			stack.pop();
			float result = performOperationFLOAT(a, b, token);
			stack.push(result);
		}
		else {
			try {
				float value = std::stof(token);
				stack.push(value);
			}
			catch (const std::invalid_argument&) {
				throw std::invalid_argument("Invalid token: " + token);
			}
		}
	}

	if (stack.size() != 1) throw std::runtime_error("Invalid expression");
	return stack.top();
}
// Function to evaluate an RPN expression
int evaluateINT(const std::vector<std::string>& tokens) {
	std::stack<int> stack;

	for (const std::string& token : tokens) {
		if (isOperator(token)) {
			if (stack.size() < 2) throw std::runtime_error("Invalid expression");
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();
			int result = performOperationINT(a, b, token);
			stack.push(result);
		}
		else {
			try {
				int value = std::stoi(token);
				stack.push(value);
			}
			catch (const std::invalid_argument&) {
				throw std::invalid_argument("Invalid token: " + token);
			}
		}
	}

	if (stack.size() != 1) throw std::runtime_error("Invalid expression");
	return stack.top();
}

bool VExpression::Is_Int() {

	bool is_int = false;
	bool is_float = false;

	for (auto ele : Elements) {
		if (ele.IsSubExpr) {
			ele.SubExpr->m_Context = m_Context;
			auto s_res = ele.SubExpr->Express();

			if (s_res->m_Type == T_Number) {
				is_int = true;
			}
			else if (s_res->m_Type == T_FloatNumber) {
				is_float = true;
				is_int = false;
			}

			int a = 5;

		}


		switch (ele.EleType) {
		case T_Ident:
		{

			VVar* fv = nullptr;
		

			fv = m_Context->FindVar(ele.VarName.GetNames());

				 
			
			if (fv->m_Type == T_Float)
			{
				is_float = true;
				is_int = false;
			}
			else if (fv->m_Type == T_Int)
			{
				is_int = true;
			}
			int bb = 5;

		}
			break;
		case T_Number:

			if (!is_float) {
				is_int = true;
				
			}

			break;
		case T_FloatNumber:
			is_int = false;
			is_float = true;
			break;
		}

	}

	if (is_float) {
		return false;
	}
	if (is_int) {
		return true;
	}

	return false;

}

bool VExpression::Is_Float() {

	bool is_int = false;
	bool is_float = false;

 	for (auto ele : Elements) {

		if (ele.IsSubExpr) {

			ele.SubExpr->m_Context = m_Context;
			auto s_res = ele.SubExpr->Express();

			if (s_res->m_Type == T_Number) {
				is_int = true;
			}
			else if (s_res->m_Type == T_FloatNumber) {
				is_float = true;
				is_int = false;
			}

			int a = 5;
			continue;
		}

		switch (ele.EleType) {
		case T_Ident:
		{
			VVar* fv = nullptr;


			fv = m_Context->FindVar(ele.VarName.GetNames());

			if (fv->m_Type == T_Float)
			{
				is_float = true;
				is_int = false;
			}
			else if (fv->m_Type == T_Int)
			{
				is_int = true;
			}
			int bb = 5;

		}
		break;
		case T_Number:

			if (!is_float) {
				is_int = true;

			}

			break;
		case T_FloatNumber:
			is_int = false;
			is_float = true;
			break;
		
		}

	}

	if (is_float) {
		return true;
	}
	if (is_int) {
		return false;
	}

	return false;

}

VVar* VExpression::Express() {

	auto con1 = m_Context;

	auto v = new VVar;

	if (Elements.size() == 1)
	{

		if (Elements[0].IsNew) {

			VVar* cls_v = new VVar;
			cls_v->m_ClassType = Elements[0].ClassType;
			cls_v->m_ClsValue = con1->CreateInstance(cls_v->m_ClassType);
			
			std::vector<VVar*> cps;
			std::vector<TokenType> sig;

			bool is_int = true;
			bool is_float = false;

			for (auto cp : Elements[0].NewParams->GetParams())
			{
				auto cv = cp->Express();
				cps.push_back(cv);
				if (cv->m_Type == T_Number) {
					is_int = true;
					sig.push_back(T_Number);
				}
				if (cv->m_Type == T_FloatNumber) {
					is_int = false;
					is_float = true;
					sig.push_back(T_FloatNumber);
				}
				int b = 5;
			}


			auto func = cls_v->m_ClsValue->FindFunctionBySig(cls_v->m_ClassType,sig);

			func->Call(Elements[0].NewParams);

			int b = 5;
			return cls_v;


		}

	}

	if (Is_Float()) {

		int a = 5;
		auto vec = ToVector();

		auto tvec = infixToPostfix(vec);

		v->m_FloatValue = evaluateFLOAT(tvec);
		v->m_Type = T_FloatNumber;

		return v;

	}
	else if (Is_Int()) {
		
		
		auto vec = ToVector();

		auto tvec = infixToPostfix(vec);

		v->m_IntValue = evaluateINT(tvec);

		v->m_Type = T_Number;

		return v;

	}


	if (Elements[0].VarName.GetNames().size() > 0)
	{
		v->m_IntValue = 0;
		auto fv = m_Context->FindVar(Elements[0].VarName.GetNames()[0]);
		v->m_IntValue = fv->m_IntValue;
		return v;

	}
	v->m_IntValue = Elements[0].IntValue;

	return v;
}

std::vector<std::string> VExpression::ToVector() {

	std::vector<std::string> stack;

	for (auto e : Elements) {

		if (e.IsSubExpr) {
			e.SubExpr->m_Context = m_Context;
			auto res = e.SubExpr->Express();


			if (res->m_Type == T_Float) {
				stack.push_back(std::to_string(res->m_FloatValue));
			}
			else if (res->m_Type == T_Number) {
				stack.push_back(std::to_string(res->m_IntValue));
			}
			continue;
		}

		switch (e.EleType) {
		case T_Ident:
		{
		//	auto fv = m_Context->FindVar(e.VarName.GetNames()[0]);
			VVar* fv = nullptr;


			fv = m_Context->FindVar(e.VarName.GetNames());
			if (fv->m_Type == T_Float)
			{
				stack.push_back(std::to_string(fv->m_FloatValue));
				//is_float = true;
				//is_int = false;

			}
			else if (fv->m_Type == T_Int)
			{
				stack.push_back(std::to_string(fv->m_IntValue));
				//is_int = true;

			}

		}

			break;
		case T_Number:

			stack.push_back(std::to_string(e.IntValue));

			break;
		case T_FloatNumber:
			stack.push_back(std::to_string(e.FloatValue));
			break;
		case T_Operator:

			switch (e.OpType) {
			case T_Plus:
				stack.push_back("+");
				break;
			case T_Times:
				stack.push_back("*");
				break;
			case T_Divide:
				stack.push_back("/");
				break;
			case T_Minus:
				stack.push_back("-");
				break;
			case T_Equal:
				stack.push_back("=");
				break;
			}

			break;
		}
//		return stack;
	}
	return stack;
}