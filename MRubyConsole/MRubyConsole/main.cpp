#include "stdafx.h"
#include "RubyMachine.h"
#include "RubyInstance.h"


enum MainFailed
{
	FILE_LOAD_ERROR = 2,
};



int main()
{
	std::shared_ptr<RubyMachine> machine = std::make_shared<RubyMachine>(); 

	FILE* file_ptr;
	fopen_s(&file_ptr, "test.rb", "rt"); 

	if (!file_ptr)
	{
		return FILE_LOAD_ERROR;
	}

	machine->LoadFile(file_ptr);
	auto inst = RubyInstance(machine, "Test");

	auto value = inst.CallFunction("get_position");
	
	std::vector<mrb_value> values;
	values.push_back(mrb_fixnum_value(10));
	values.push_back(mrb_fixnum_value(10));

	auto state = machine->getState();
	inst.CallFunction("move_to", values); 


	fclose(file_ptr);
}