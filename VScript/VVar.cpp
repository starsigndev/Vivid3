#include "pch.h"
#include "VVar.h"

VVar::VVar() {



}

void VVar::Transfer(VVar* r) {

	this->m_ArrValues = r->m_ArrValues;
	this->m_BoolValue = r->m_BoolValue;
	this->m_ClassType = r->m_ClassType;
	this->m_ClsValue = r->m_ClsValue;
	this->m_FloatValue = r->m_FloatValue;
	this->m_IntValue = r->m_IntValue;
	this->m_Name = r->m_Name;
	this->m_StrValue = r->m_StrValue;
	this->m_Type = r->m_Type;
	this->m_Lambda = r->m_Lambda;

}

void VVar::SetArray(int index, VVar* from)
{

	m_ArrValues[index] = from;


}