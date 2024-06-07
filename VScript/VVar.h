#pragma once
#include <string>
#include <vector>
#include "VClass.h"

class VVar
{
public:

	std::string m_Name = "";
	int m_IntValue = 0;
	float m_FloatValue = 0.0f;
	std::string m_StrValue = "";
	bool m_BoolValue = false;
	VClass* m_ClsValue = nullptr;
	std::vector<VVar*> m_ArrValues;
	TokenType m_Type;
	std::string m_ClassType = "";
	float ToFloat() {
		if (m_Type == T_FloatNumber) {
			return m_FloatValue;
		}
		else {
			return (float)m_IntValue;
		}
	}
	int ToInt() {
		if (m_Type == T_Number) {
			return m_IntValue;
		}
		return (int)m_FloatValue;

	}

};

