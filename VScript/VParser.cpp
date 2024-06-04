#include "pch.h"
#include "VParser.h"
#include "VClass.h"
#include "VVarGroup.h"
#include "VFunction.h"
#include "VDefineParams.h"

VParser::VParser() {

}

VModule* VParser::ParseModule(VTokenStream stream) {

	m_Stream = stream;

	VModule* module = new VModule;

	auto token = m_Stream.GetNext();

	Assert(token.GetType() == T_Module, "Expected 'module' keyword.");

	auto name = ParseName();

	module->SetName(name);


	while (!m_Stream.End()) {

		auto token = m_Stream.GetNext();

		switch (token.GetType()) {
		case T_Class:
		{
			auto p_class = ParseClass();
			int aa = 1;
			module->AddClass(p_class);

		}
			break;
		default:
			Err("Unexpected token in module:" + token.GetLex());
			break;
		}

		int b = 5;

	}

	return module;

}

VName VParser::ParseName() {

	std::vector<std::string> names;

	while (true) {

		auto tok = m_Stream.GetNext();
		if (tok.GetType() == T_Ident) {
			names.push_back(tok.GetLex());
		}
		else if (tok.GetType() == T_Access)
		{

		}
		else {
			m_Stream.Back();
			break;
		}

	}

	return VName(names);

}

VClass* VParser::ParseClass() {

	auto name = ParseName();

	auto n_cls = new VClass;

	n_cls->SetName(name);

	if (m_Stream.GetNext().GetType() == T_End) {

		//m_Stream.Back();
		return n_cls;

	}
	else {

		m_Stream.Back();

	}

	while (!m_Stream.End()) {

		auto token = m_Stream.GetNext();

		switch (token.GetType()) {
		case T_Func:
		{
			int bb = 5;
			VFunction* func = ParseFunction();
		}
			break;
		case T_End:

			return n_cls;

			break;
		case T_Int:
		case T_Float:
		case T_String:
		case T_Bool:

			VVarGroup* group = new VVarGroup(token.GetType());
			n_cls->AddVarGroup(group);


			while (!m_Stream.End()) {

				auto peek = m_Stream.Peek(0);

				if (peek.GetLex() == ",")
				{
					m_Stream.GetNext();
					continue;
				}
				if (peek.GetType() == T_EOL) {

					//n_cls->AddVars(
					//)
					m_Stream.GetNext();
					break;

				}
				auto v_name = ParseName();
				group->AddName(v_name,nullptr);

			}

			break;
		}

		int a = 5;

	}

	m_Stream.Back();

	return n_cls;

	
}

VFunction* VParser::ParseFunction() {

	//auto token = m_Stream.GetNext();

	auto name = ParseName();

	VFunction* func = new VFunction;
	func->SetName(name);

	auto next = m_Stream.GetNext();

	if (next.GetLex() == "()")
	{
		return func;
	}
	else {

		auto pars = ParseParameters();
		int aa = 5;

	}

	int a = 5;

	return nullptr;
}

VDefineParams* VParser::ParseParameters() {

	VDefineParams* params = new VDefineParams;

	while (!m_Stream.End()) {
	
		auto token = m_Stream.GetNext();
		if (token.GetLex() == ",")
		{
			continue;
		}
		if (token.GetLex() == ")")
		{
			return params;
		}
		auto name = ParseName();
		VParameter* new_param = new VParameter;
		if (m_Stream.Peek(0).GetLex() == "=")
		{

		}

	
		new_param->SetType(token.GetType());
		new_param->SetName(name);


		params->AddParam(new_param);

	}
	int b = 5;

	return nullptr;

}

void VParser::Err(std::string msg) {

	printf("Error parsing.\n");
	printf(msg.c_str());
	printf("\n");

}

void VParser::Assert(bool value, std::string msg)
{
	if (!value) {
		Err(msg);
		exit(0);
	}
}