#include "pch.h"
#include "VParameter.h"

VParameter::VParameter() {

	m_Default = nullptr;


}

void VParameter::SetName(VName name) {

	m_Name = name;

}

void VParameter::SetType(TokenType type) {

	m_Type = type;

}

void VParameter::SetDefaultExpression(VExpression* expr) {

	m_Default = expr;

}