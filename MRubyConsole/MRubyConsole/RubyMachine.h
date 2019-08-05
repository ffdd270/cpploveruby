#ifndef RUBY_MACHINE_H
#define RUBY_MACHINE_H

typedef mrb_value ruby_instance;

//Low-Level Machine. 
//단순 mrb 함수들의 와퍼 클래스.
class RubyMachine
{
public:
	RubyMachine(); 

	//Add Codes.
	//--------------------------------------------------
	mrb_value LoadFile(FILE *);
	mrb_value LoadString(std::string line);
	//--------------------------------------------------

	//Call Codes.
	//--------------------------------------------------
	mrb_value CallGlobalFunction(std::string function_name, std::vector<mrb_value> params);
	mrb_value CallGlobalFunction(std::string function_name);

	mrb_value CallInstanceFunction(mrb_value ruby_instance, std::string function_name, std::vector<mrb_value> params);
	mrb_value CallInstanceFunction(mrb_value ruby_instance, std::string function_name);
	//--------------------------------------------------

	//Create Instance
	//--------------------------------------------------
	mrb_value CreateInstance(std::string className);
	mrb_value CreateInstance(std::string className, std::vector<mrb_value> params);
	//--------------------------------------------------

	//Create Values( Only Can Get Value to use MRB)
	//--------------------------------------------------
	mrb_sym CreateSymbol(std::string symbolName); 
	mrb_value CreateString(std::string string);
	mrb_value CreateFixNum(int number); 
	//--------------------------------------------------

	//C++ API Insert
	//--------------------------------------------------
	RClass* DefineModule(std::string moduleName);
	//parent가 nullptr이면, object_class를 기본으로..
	RClass* DefineClass(std::string className, RClass * parent = nullptr);
	void DefineMethod(std::string className, mrb_func_t function, RClass * object);
	//--------------------------------------------------

	mrb_state* getState();

	~RubyMachine();
private: 
	mrb_value createInstance(std::string className, mrb_value* params, int lenght);
	mrb_value callFunction(mrb_value ruby_instance, std::string function_name, mrb_value * params, int lenght);
	mrb_state * createState(); 

private:
	mrb_state* state; 
};




#endif 

