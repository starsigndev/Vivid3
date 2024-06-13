#pragma once
#include <string>
#include <vector>
#include <functional>

class VContext;
class VClass;
class VVar;
class VModule;

class ScriptHost
{
public:

	ScriptHost();
	VModule* LoadModule(std::string path);
	VClass* CreateInstance(std::string name);
	void AddCFunction(std::string name, std::function<VVar* (const std::vector<VVar*>& args)> func);
	VVar* CRVec3(float x, float y, float z);
private:

	VContext* m_Context;
	VModule* m_Vec3, * m_Vec4;
	VModule* m_Matrix;
	VModule* m_Node;
	VModule* m_GS;

};



