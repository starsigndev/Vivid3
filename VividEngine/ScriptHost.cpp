#include "pch.h"
#include "ScriptHost.h"
#include "VContext.h"
#include "VModule.h"
#include "VSource.h"
#include "VTokenizer.h"
#include "VParser.h"
ScriptHost::ScriptHost() {

	m_Context = new VContext;

    m_Vec3 = LoadModule("v/mods/maths/Vec3.v");
    m_Vec4 = LoadModule("v/mods/maths/Vec4.v");
    m_Matrix = LoadModule("v/mods/maths/matrix.v");
    m_Node = LoadModule("v/mods/scene/node.v");
    m_GS = LoadModule("v/Gamescript.v");

	//import modules



}

VModule* ScriptHost::LoadModule(std::string path) {

    VSource* mod_src = new VSource(path);
      

    VTokenizer* toker = new VTokenizer();
    auto stream = toker->Tokenize(mod_src);
    
 
    VParser* parser = new VParser;

    VModule* com_mod = parser->ParseModule(stream);

    m_Context->AddModule(com_mod);

    //VContext* con1 = new VContext;
    //con1->AddModule(test_mod);
    return com_mod;

}

VClass* ScriptHost::CreateInstance(std::string name) {

    return m_Context->CreateInstance(name);


}

void ScriptHost::AddCFunction(std::string name, std::function<VVar* (const std::vector<VVar*>& args)> func)
{

    m_Context->RegisterCFunc(name, func);

}

VVar* ScriptHost::CRVec3(float x, float y, float z) {

    auto v3 = CreateInstance("Vec3");
    VVar* res = new VVar;

    v3->FindVar("X")->SetFloat(x);
    v3->FindVar("Y")->SetFloat(y);
    v3->FindVar("Z")->SetFloat(z);
    res->SetType(T_Class);
    res->SetClassType("Vec3");
    res->SetClassValue(v3);

    return res;
}