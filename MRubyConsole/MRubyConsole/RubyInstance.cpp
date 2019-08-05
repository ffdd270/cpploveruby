#include "stdafx.h"
#include "RubyInstance.h"

#include "RubyMachine.h"


RubyInstance::RubyInstance(std::weak_ptr<RubyMachine> machine, std::string className) : isCreate(false)
{
	auto instance = machine.lock();

	if (instance)
	{
		this->instance = instance->CreateInstance(className);
		this->machine = machine;
		isCreate = true;
	}
	else
	{
		machineIsDead();
	}
}

RubyInstance::RubyInstance(std::weak_ptr<RubyMachine> machine, std::string className, std::vector<mrb_value> params)
{
	auto instance = machine.lock();

	if (instance)
	{
		this->instance = instance->CreateInstance(className, params);
		this->machine = machine;
		isCreate = true;
	}
	else
	{
		machineIsDead();
	}
}

mrb_value RubyInstance::CallFunction(std::string methodName)
{
	auto machine_instance = machine.lock();
	if (machine_instance)
	{
		return machine_instance->CallInstanceFunction(instance, methodName); 
	}
	else
	{
		machineIsDead();
		return mrb_value();
	}
}

mrb_value RubyInstance::CallFunction(std::string methodName, std::vector<mrb_value> params)
{
	auto machine_instance = machine.lock();
	if (machine_instance)
	{
		return machine_instance->CallInstanceFunction(instance, methodName, params);
	}
	else
	{
		machineIsDead();
		return mrb_value();
	}
}

mrb_value RubyInstance::GetValue(std::string valueName)
{
	return mrb_value();
}

void RubyInstance::machineIsDead()
{
	puts("Instance Is Not Valied;");
}
