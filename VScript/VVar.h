#pragma once
#include <string>
#include <vector>
#include "VClass.h"

class VVar
{
public:
	
	VVar();
	void Transfer(VVar* other);
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
	std::string ToString() {
		return m_StrValue;
	}
	void SetName(std::string name) {
		m_Name = name;
	}
	void SetInt(int value) {
		m_IntValue = value;
	}
	void SetFloat(float value) {
		m_FloatValue = value;
	}
	void SetType(TokenType type) {
		m_Type = type;
	}
	void SetClassType(std::string type) {
		m_ClassType = type;
	}
	void SetArray(int index, VVar* value);
	VVar* GetArray(int index) {
		return m_ArrValues[index];
	}
	void SetClassValue(VClass* cls)
	{
		m_ClsValue = cls;
	}
	VClass* GetClassValue()
	{
		return m_ClsValue;
	}
	bool IsName(std::string name) {
		return name == m_Name;
	}
	bool IsType(TokenType type) {
		return m_Type == type;
	}
	std::string GetClassType() {
		return m_ClassType;
	}
	void SetString(std::string str)
	{
		m_StrValue = str;
	}
	TokenType GetType()
	{
		return m_Type;
	}
private:

	std::string m_Name = "";
	int m_IntValue = 0;
	float m_FloatValue = 0.0f;
	std::string m_StrValue = "";
	bool m_BoolValue = false;
	VClass* m_ClsValue = nullptr;
	std::vector<VVar*> m_ArrValues;
	TokenType m_Type;
	std::string m_ClassType = "";
	

};

