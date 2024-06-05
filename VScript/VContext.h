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
            v->m_IntValue = params->GetParams()[ii]->Express()->m_IntValue;
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

    VVar* FindVar(std::string name);

private:

    VName m_Check;
    VModule* m_Return = nullptr;
	std::vector<VModule*> m_Modules;
    std::map < std::string, std::function<VVar* (std::initializer_list<VVar*>)>> m_CFuncMap;
    std::stack<VScope*> m_ScopeStack;
};

