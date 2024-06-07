#include "pch.h"
#include "VContext.h"
#include "VScope.h"

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

VVar* VContext::FindVar(std::vector<std::string> names) {

	if (names.size() == 1)
	{
		return FindVar(names[0]);
	}
	else {

		VVar* cur = FindVar(names[0]);
		if (cur->m_ClsValue == nullptr) {
			printf("Runtime error:");
			printf(names[0].c_str());
			printf(" is null.\n");
			exit(1);
		}
		int ii = 1;
		while (true) {
			
			if (cur->m_ClsValue != nullptr) {
				auto ncur = cur->m_ClsValue->FindVar(names[ii]);
				if (ncur != nullptr) {
					cur = ncur;
				}
				else {
					return cur;
				}

			}

			ii++;
			if (ii >= names.size()) {
				return cur;
			}
		}

	}

}

VVar* VContext::FindVar(std::string name) {

	m_ScopeStack.top()->SetContext(this);
	auto var = m_ScopeStack.top()->FindVar(name);
	if (var != nullptr) {
		return var;
	}
	return nullptr;
}