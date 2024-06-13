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
	void AddStaticVarGroup(VVarGroup* group);
	void AddFunction(VFunction* func);
	void AddStaticFunction(VFunction* func)
	{
		m_StaticFuncs.push_back(func);
	}
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
	std::vector<VFunction*> GetFunctions();
	void SetScope(VScope* scope) {
		m_InstanceScope = scope;
	}
	void CreateScope();
	void SetStatic(bool stat) {
		m_Static = stat;
	}
	std::vector<VFunction*> GetStaticFuncs() {
		return m_StaticFuncs;
	}
	void SetSubClass(std::string name);
	std::string GetSubClass();

private:

	bool m_Static = false;
	VContext* m_Context;
	VName m_Name;
	std::vector<VVarGroup*> m_StaticGroups;
	std::vector<VFunction*> m_StaticFuncs;
	std::vector<VVarGroup*> m_Groups;
	std::vector<VFunction*> m_Funcs;
	VScope* m_InstanceScope = nullptr;
	std::string m_SubClass = "";
};

