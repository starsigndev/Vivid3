#pragma once
#include "VSource.h"
#include "VTokenStream.h"

class VTokenizer
{
public:

	VTokenizer();
	VTokenStream Tokenize(VSource* source);
	void TokenizeWord();
	void TokenizeNumber();
	

private:

	VSource* m_Source;
	VTokenStream m_TokenStream;

};

