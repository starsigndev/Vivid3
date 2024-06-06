#pragma once
#include <vector>
#include <string>
#include "VToken.h"

class VTokenStream
{
public:
	VTokenStream();
	void AddToken(VToken token);
	VToken GetNext();
	VToken Peek(int delta);
	std::vector<VToken> GetTokens();
	bool End();
	void Back();
	bool LineHas(TokenType type);
	bool LineHas(std::string lex);

private:
	std::vector<VToken> m_Tokens;
	int m_Index = 0;
};


