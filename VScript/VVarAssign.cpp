#include "pch.h"
#include "VVarAssign.h"
#include "VContext.h"


VVar* VVarAssign::Exec() {

	auto con = GetContext();

	m_Expr->m_Context = con;


	auto fv =con->FindVar(m_Name.GetNames()[0]);

	fv->m_IntValue = m_Expr->Express()->m_IntValue;



	return nullptr;
}