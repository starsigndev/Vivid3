#include "pch.h"
#include "VFunction.h"
#include "VCodeBody.h"
#include "VClass.h"
#include "VContext.h"
#include "VDefineParams.h"
#include "VCallParameters.h"

VFunction::VFunction() {

}

void VFunction::SetName(VName name) {

	m_Name = name;

}

VName VFunction::GetName() {

	return m_Name;

}

void VFunction::SetParams(VDefineParams* params) {

	m_Params = params;

}

VDefineParams* VFunction::GetParams() {

	return m_Params;

}

void VFunction::SetContext(VContext* context) {

	m_Context = context;
	m_Code->SetContext(m_Context);

}

VFunction* VFunction::Clone() {

	VFunction* clone = new VFunction;
	clone->SetName(m_Name);
	clone->SetParams(m_Params);
	clone->SetBody(m_Code);
	clone->SetContext(m_Context);
	return clone;

}

VVar* VFunction::Call(VCallParameters* params) {

	m_Context->PushScope(m_ClassOwner->GetScope());

	if (params != nullptr) {
		m_Context->PushScope(GetScope(), params);
	}
	else {
		m_Context->PushScope(GetScope());
	}

	auto res = m_Code->Exec();

	m_Context->PopScope();

	m_Context->PopScope();

	return res;
}

void VFunction::SetBody(VCodeBody* code) {

	m_Code = code;

}

void VFunction::SetOwner(VClass* cls) {

	m_ClassOwner = cls;

}

VScope* VFunction::GetScope() {

	auto r = new VScope;

	auto params = GetParams();

	if (params != nullptr)
	{

		if (params->GetParams().size() > 0) {

			auto pp = params->GetParams();

			for (auto p : pp) {

				VVar* f_var = new VVar;
				f_var->m_Name = p->GetName().GetNames()[0];
				f_var->m_Type = p->GetType();
				f_var->m_ClassType = p->GetClassType();
				f_var->m_ClsValue = nullptr;
				r->RegisterVar(f_var);

			}
		}
	}

	r->SetClass(m_ClassOwner);
	return r;
	


}