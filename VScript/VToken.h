#pragma once
#include<string>

enum TokenType {
	T_Ident, T_Number, T_If, T_Else, T_End, T_Then, T_While, T_For, T_Func, T_Meth, T_Operator, T_None, T_Class, T_Module, T_Access,
	T_Int, T_Float, T_String, T_Bool, T_EOL
};

class VToken
{
public:

	VToken(TokenType type, std::string lexeme);
	void SetPlace(int start, int end);
	std::string GetLex();
	TokenType GetType();

private:

	TokenType m_TokenType = TokenType::T_None;
	std::string m_Lexeme = "";
	int m_SourceStart = 0;
	int m_SourceEnd = 0;

};


