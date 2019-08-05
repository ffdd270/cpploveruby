#ifndef RUBY_INSTANCE
#define RUBY_INSTANCE

class RubyMachine;

class RubyInstance
{
public: 
	RubyInstance( std::weak_ptr<RubyMachine> machine, std::string className );
	RubyInstance( std::weak_ptr<RubyMachine> machine, std::string className, std::vector<mrb_value> params );

	mrb_value CallFunction(std::string methodName);
	mrb_value CallFunction(std::string methodName, std::vector<mrb_value> params);

	mrb_value GetValue(std::string valueName);
private:
	void machineIsDead();

private:
	std::weak_ptr<RubyMachine> machine; 

	mrb_value instance;
	bool isCreate; 
};


#endif 