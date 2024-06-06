#pragma once
#include <vector>
#include <string>
#include "VName.h"
#include "VVarGroup.h"

class VFunction;
class VContext;
class VScope;

class VClass
{
public:

	void SetName(VName name);
	void AddVarGroup(VVarGroup* group);
	void AddFunction(VFunction* func);
	VFunction* FindFunction(VName name);
	void SetContext(VContext* context);
	VClass* Clone();
	VName GetName();
	VFunction* FindFunction(std::string name);
	VFunction* FindFunctionBySig(std::string name,std::vector<TokenType> sig);
	VVar* FindVar(std::string name);
	VScope* GetScope() {
		return m_InstanceScope;
	}
	void SetScope(VScope* scope) {
		m_InstanceScope = scope;
	}
	void CreateScope();

private:


	VContext* m_Context;
	VName m_Name;
	std::vector<VVarGroup*> m_Groups;
	std::vector<VFunction*> m_Funcs;
	VScope* m_InstanceScope = nullptr;

};

