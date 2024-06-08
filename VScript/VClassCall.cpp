#include "pch.h"
#include "VClassCall.h"
#include "VVar.h"
#include "VCallParameters.h"
#include "VContext.h"
#include "VFunction.h"

VVar* VClassCall::Exec() {

	int a = 5;
	auto cv = GetContext()->FindVar(m_Name.GetNames());
	auto func = cv->GetClassValue()->FindFunction(m_Name.GetNames()[m_Name.GetNames().size() - 1]);
	
	for (auto p : m_Params->GetParams()) {

		p->m_Context = GetContext();

	}
	func->SetContext(GetContext());

	return func->Call(m_Params);

	return nullptr;

}