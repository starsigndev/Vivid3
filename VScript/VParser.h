#pragma once
#include "VToken.h"
#include "VTokenStream.h"
#include "VModule.h"

class VName;
class VClass;
class VFunction;
class VDefineParams;

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

private:

	VTokenStream m_Stream;

};

