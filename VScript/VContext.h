#pragma once
#include "VClass.h"
#include "VModule.h"
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <stack>
#include "VVar.h"
#include "VScope.h"
#include "VCallParameters.h"
#include "VExpression.h"


class VContext
{
public:

    VContext();
	void AddModule(VModule* module);
    
    VModule* GetModule() {

        for (auto mod : m_Modules) {

            if (m_Check.SameName(mod->GetName())) {
                m_Return = mod;
                return mod;
            }

        }
        m_Check = VName();
        

        return nullptr;

    }
    
    template <typename T, typename... Args>
    VModule* GetModule(T first, Args... args) {
    //    std::cout << "Processing: " << first << std::endl;
        // Recursively call the member function with the remaining arguments
        m_Check.Add(first);
        GetModule(args...);
        return m_Return;
    }

    VClass* CreateInstance(std::string name);
    void RegisterCFunc(std::string name, std::function<VVar* (std::initializer_list<VVar*>)> func)
    {

        m_CFuncMap[name] = func;

    }

    std::function<VVar* (std::initializer_list<VVar*>)> FindCFunc(std::string name) {

        auto it = m_CFuncMap.find(name);
        if (it != m_CFuncMap.end()) {
            // Step 4: Get the value associated with the key
            return it->second;
            //    std::cout << "Key: " << key << ", Value: " << it->second << std::endl;
        }
        else {

            //std::cout << "Key: " << key << " not found in the map." << std::endl;
        }
        return nullptr;
    }
    void PushScope(VScope* scope, VCallParameters* params) {
        VScope* root = nullptr;

        if (m_ScopeStack.size() > 0) {
            root = m_ScopeStack.top();
        }
        int pc = params->GetParams().size();
        int ii = 0;
        for (auto v : scope->GetVars()) {
            if (ii >= pc) {
                break;
            }
            
            params->GetParams()[ii]->m_Context = this;
           auto pres= params->GetParams()[ii]->Express();
           auto pn = v->GetName();


           //v->Transfer(pres);
           v->SetInt(pres->ToInt());
           v->SetFloat(pres->ToFloat());
           v->SetString(pres->ToString());
           v->SetArrayData(pres->GetArrayData());
           v->SetLambda(pres->GetLambda());
           v->SetClassValue(pres->GetClassValue());
           v->SetName(pn);

           /*
           * 
            switch (v->m_Type) {
            case T_String:
            {
                int a = 5;
                v->m_StrValue = pres->m_StrValue;
                
            }
                break;
            case T_Int:
            {
                int a = 5;
                switch (pres->m_Type) {
                case T_Number:
                    v->m_IntValue = pres->m_IntValue;
                    break;
                case T_FloatNumber:
                    v->m_IntValue = (int)pres->m_FloatValue;
                    break;
              
                }
            }
            break;
            case T_Float:
            {
                switch (pres->m_Type) {
                case T_Number:
                    v->m_FloatValue = pres->m_IntValue;
                    break;
                case T_FloatNumber:
                    v->m_FloatValue = (int)pres->m_FloatValue;
                    break;

                }
                int b = 5;
            }
            break;
              case T_Class:
                    v->m_ClsValue = pres->m_ClsValue;
                    v->m_ClassType = pres->m_ClassType;
                    break;
            }
            */
            ii++;
        }
        m_ScopeStack.push(scope);
        if (root != nullptr) {
            scope->SetRoot(root);
        }
    }
    void PushScope(VScope* scope) {

        VScope* root = nullptr;

        if (m_ScopeStack.size() > 0) {
           root = m_ScopeStack.top();
        }
        scope->SetContext(this);
        m_ScopeStack.push(scope);
        if (root != nullptr) {
            scope->SetRoot(root);
        }

    }

    void PopScope() {
        m_ScopeStack.pop();
    }

    VFunction* FindFunc(std::string name) {

        auto func = m_ScopeStack.top()->FindFunc(name);
        return func;

    }

    VFunction* FindFunc(std::string name, std::vector<TokenType> sig)
    {
        return nullptr;
      //  return m_ScopeStack.top()->FindFunc(name, sig);
    }

    VScope* GetTopScope() {
        return m_ScopeStack.top();
    }

    VVar* FindVar(std::string name);
    VVar* FindVar(std::vector<std::string> names);

private:

    VName m_Check;
    VModule* m_Return = nullptr;
	std::vector<VModule*> m_Modules;
    std::map < std::string, std::function<VVar* (std::initializer_list<VVar*>)>> m_CFuncMap;
    std::stack<VScope*> m_ScopeStack;
    VScope* m_StaticScope;
};

