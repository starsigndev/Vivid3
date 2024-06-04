#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class VSource
{
public:

	VSource(std::string path);
	std::string GetCode();
	int GetNext();
	void Back();

private:

	std::string m_Source;
	int m_Index = 0;

};

