// VScriptTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "VModule.h"
#include "VParser.h"
#include "VSource.h"
#include "VTokenizer.h"
#include "VTokenStream.h"
#include "VContext.h"
#include "VFunction.h"
#include "VAction.h"
#include "VVar.h"
#include <vector>

VVar* TestDebug(const std::vector<VVar*>& args)
{
    int b = 5;

    std::vector<VVar*> vec(args);

    printf("DebugS:");
    printf("%f",vec[0]->ToFloat());
    printf("\n");

    //printf("Debug1:%d\n",vec[0]->ToInt());

 //   printf("Debug2:%f\n", vec[0]->ToFloat());

    return nullptr;
}

int main()
{
    std::cout << "VScript - Test!\n\n\n\n";

    VSource* test = new VSource("test/test1.v");

    std::cout << test->GetCode() << std::endl;

    VTokenizer* toker = new VTokenizer();
    auto stream = toker->Tokenize(test);
    int b = 5;
    std::cout << "TokenStream>>" << std::endl;

    for (auto token : stream.GetTokens()) {

        std::cout << "Token:" << token.GetLex() << std::endl;

    }


    VParser* parser = new VParser;
    
    VModule* test_mod = parser->ParseModule(stream);
    
    VContext* con1 = new VContext;
    con1->AddModule(test_mod);
    con1->RegisterCFunc("debug", TestDebug);
    auto i1 = con1->CreateInstance("TestClass");
    auto f1 = i1->FindFunction("TestClass");


    auto v1 = i1->FindVar("C");

    auto t1 = new VVar;

//e    v1->SetC((void*)t1);

  //  f1->Call(nullptr);

    auto mod1 = con1->GetModule("Vivid", "Test");

    int a = 5;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
