#include "pch.h"
#include "VContext.h"

void VContext::AddModule(VModule* module) {

	auto mod = module->Clone();
	
	m_Modules.push_back(mod);


}

VClass* VContext::CreateInstance(std::string name) {

	for (auto mod : m_Modules) {

		auto c_class = mod->FindClass(name);
		if (c_class != nullptr) {
			auto i_class = c_class->Clone();
			i_class->SetContext(this);
			i_class->CreateScope();
			return i_class;
		}

	}

	return nullptr;

}

VVar* VContext::FindVar(std::string name) {

	auto var = m_ScopeStack.top()->FindVar(name);
	if (var != nullptr) {
		return var;
	}
}