#pragma once
#include "VClass.h"
#include "VModule.h"
#include <vector>
#include <string>

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

private:

    VName m_Check;
    VModule* m_Return = nullptr;
	std::vector<VModule*> m_Modules;
};

