#include "stdafx.h" 
#include "RubyMachine.h"
#include "RubyValues.h"

RubyMachine::RubyMachine()
{
	state = createState(); 

	if (!state)
	{
		throw "Ruby Machine Create Failed."; 
	}
}

mrb_value RubyMachine::LoadFile(FILE* file)
{
	return mrb_load_file(state, file);
}

mrb_value RubyMachine::LoadString(std::string line)
{
	auto value = mrb_load_string(state, line.c_str());

	return value;
}

mrb_value RubyMachine::CallGlobalFunction(std::string function_name, std::vector<mrb_value> params)
{
	auto top_self_instnace = mrb_obj_value(state->top_self);
	int size = params.size(); 
	auto params_ptr = params.data();

	return callFunction(top_self_instnace, function_name, params_ptr, size);
}

mrb_value RubyMachine::CallGlobalFunction(std::string function_name)
{
	auto top_self_instnace = mrb_obj_value(state->top_self);

	return callFunction(top_self_instnace, function_name, nullptr, 0);
}

mrb_value RubyMachine::CallInstanceFunction(mrb_value ruby_instance, std::string function_name, std::vector<mrb_value> params)
{
	int size = params.size();
	auto params_ptr = params.data();

	return callFunction(ruby_instance, function_name, params_ptr, size);
}

mrb_value RubyMachine::CallInstanceFunction(mrb_value ruby_instance, std::string function_name)
{
	return callFunction(ruby_instance, function_name, nullptr, 0);
}

mrb_value RubyMachine::CreateInstance(std::string className)
{
	return createInstance(className, nullptr, 0); 
}

mrb_value RubyMachine::CreateInstance(std::string className, std::vector<mrb_value> params)
{
	return createInstance(className, params.data(), params.size()); 
}

mrb_sym RubyMachine::CreateSymbol(std::string symbolName)
{
	return mrb_intern(state, symbolName.c_str(), symbolName.size());
}

mrb_value RubyMachine::CreateString(std::string string)
{
	return mrb_str_new(state, string.c_str(), string.size());
}

mrb_value RubyMachine::CreateFixNum(int number)
{
	return RubyValues::GetRubyFixNum(number);
}

RClass* RubyMachine::DefineModule(std::string moduleName)
{
	return nullptr;
}

RClass* RubyMachine::DefineClass(std::string className, RClass* parent)
{
	if (parent == nullptr)
	{
		parent = state->object_class; 
	}

	return mrb_define_class(state, className.c_str, parent);
}

void RubyMachine::DefineMethod(std::string className, mrb_func_t function, RClass* object)
{
	return mrb_define_method(state, object, className.c_str, function, MRB_ARGS_NONE());
}

mrb_state* RubyMachine::getState()
{
	return state;
}

mrb_value RubyMachine::createInstance(std::string className, mrb_value* params, int lenght)
{
	return mrb_class_new_instance(state, lenght, params, mrb_class_get( state , className.c_str())); 
}

mrb_value RubyMachine::callFunction(mrb_value ruby_instance, std::string function_name, mrb_value* params, int lenght)
{
	auto symbol = mrb_intern_cstr(state, function_name.c_str()); 

	return mrb_funcall_argv(state, ruby_instance, symbol, lenght, params);
}

mrb_state * RubyMachine::createState()
{
	auto state = mrb_open();
	if (!state) 
	{
		puts("STATE CREATE FAILED!");
		return nullptr; 
	}

	return state;
}

RubyMachine::~RubyMachine()
{
	mrb_close(state);
	state = nullptr; 
}
