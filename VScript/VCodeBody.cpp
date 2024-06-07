#include "pch.h"
#include "VCodeBody.h"

void VCodeBody::AddCode(VAction* action) {

	m_Code.push_back(action);

}

VVar* VCodeBody::Exec() {

	for (auto code : m_Code) {

		//code->SetContext(GetContext());

		auto res = code->Exec();
		if (res != nullptr) {
			return res;
		}

	}
	return nullptr;
}

void VCodeBody::SetContext(VContext* context) {

	for (auto code : m_Code) {
		
		code->SetContext(context);

	}

}