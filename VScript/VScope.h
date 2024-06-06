#pragma once
#include <vector>
#include <string>

class VVar;
class VClass;
class VFunction;

class VScope
{
public:

	void RegisterVar(VVar* var);
	VVar* FindVar(std::string name);
	void NoRoot() {
		m_NoRoot = true;
	}
	VFunction* FindFunc(std::string name);

	void SetClass(VClass* cls);
	void SetRoot(VScope* root) {
		m_RootScope = root;
	}
	std::vector<VVar*> GetVars() {
		return m_LocalVars;
	}
private:

	VScope* m_RootScope = nullptr;
	std::vector<VVar*> m_LocalVars;
	bool m_NoRoot = false;
	VClass* m_Owner = nullptr;

};

