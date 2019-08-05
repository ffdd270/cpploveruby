#ifndef RUBY_VALUES_H
#define RUBY_VALUES_H


//Static Class! 

//런타임 이외에서도 가능한 것들은 여기로.. 
class RubyValues
{
public:
	//C++ -> Ruby
	//--------------------------------
	static mrb_value GetRubyFixNum(int number);
	//--------------------------------

private:
};

#endif 

