#include "stdafx.h" 

using namespace std;


const char* WELCOME_MESSAGE = "Executing Ruby code from C!";


mrb_state* get_state()
{
	mrb_state* mrb = mrb_open();
	if (!mrb) {
		return nullptr;
	}
	puts(WELCOME_MESSAGE);

	return mrb;
}

void load_string_and_return()
{
	auto mrb = get_state();

	if (!mrb) { return; }

	//라인 - 바이 - 라인으로 집어 넣을 수도 있습니다. 
	auto value = mrb_load_string(mrb, "5.times { p 'hello world!' } ");

	//반환 값은 union으로 되어있어용. 
	//int, symbol(int), float과 void *가 있습니당. 
	//타입은 tt로 받아올 수 있어용. 
	std::cout << value.value.i << std::endl;

	puts("load_string_and_return end!");

	mrb_close(mrb);
}

void load_string_and_get_string()
{
	auto mrb = get_state(); 
	if (!mrb) { return; }

	auto value = mrb_load_string(mrb, "return \"string\"");
	
	if (mrb_type(value) == mrb_vtype::MRB_TT_STRING) //타입체킹!
	{
		auto string = mrb_str_to_cstr(mrb, value); //mruby/string 헤더 필요. 기본 제공 그런거 없다. 
		puts(string);
	}
	puts("load_string_and_get_strings end!");

	mrb_close(mrb);
}

void load_string_and_function_call()
{
	auto mrb = get_state();
	if (!mrb) { return; }

	auto value = mrb_load_string(mrb, "\
			def test_proc(name, number)\
				number.times { |i| puts \"#{name} : to #{i} \" }\
			end\
		");

	//함수 호출을 위해선 심볼이 필요하다. 
	mrb_sym function_symbol = mrb_intern_lit(mrb, "test_proc"); //루비 스테이트, 만들 심볼 이름. 


/** 한글 번역. 원문은 mrby.h 파일에 존재하는 주석입니다.
 *  이미 존재하고 있는 루비 함수들을 호출합니다. 이 함수는 기본적으로 타입 안전한 mrb_funcall의 버전입니다.
 *
 *      #include <stdio.h>
 *      #include <mruby.h>
 *      #include "mruby/compile.h"
 *      int
 *      main()
 *      {
 *        mrb_int i = 99;
 *        mrb_state *mrb = mrb_open();
 *
 *        if (!mrb) { }
 *        mrb_sym m_sym = mrb_intern_lit(mrb, "method_name"); //메서드의 심볼
 *
 *        FILE *fp = fopen("test.rb","r");
 *        mrb_value obj = mrb_load_file(mrb,fp);
 *        mrb_funcall_argv(mrb, obj, m_sym, 1, &obj); // test.rb에서부터 루비 함수를 호출합니다.
*		  //load_string 안하고도 이렇게 할수 있다는 걸 보여주는 것 같아용
 *        fclose(fp);
 *        mrb_close(mrb);
 *       }
 * @param [mrb_state*] mrb_state* 현재 mruby의 mrb_state입니다.
 * @param [mrb_value] mrb_value 참조해야 할 mruby 값입니다. (역주 : ruby에선 함수를 생성할 시 함수를 돌려주더라고요. )
 * @param [mrb_sym] mrb_sym 메서드를 대표하는 심볼입니다.
 * @param [mrb_int] mrb_int 이 함수의 매개변수가 몇개인지 알려줘야 합니다.
 * @param [const mrb_value*] mrb_value* 매개변수들의 포인터입니다.
 * @return [mrb_value] mrb_value mruby 함수의 반환값입니다.
 * @see mrb_funcall
 */

	mrb_value params[2];
		
	const char* name = "HaruGakkaP";

	params[0] = mrb_str_new(mrb, name, strlen(name));
	params[1] = mrb_fixnum_value(3);

	auto top_class_value = mrb_obj_value(mrb->top_self); //루비는 모든게 클래스입니다. 
	//즉. 전역 영역도 'top_self'라는 클래스로 표현됩니다. 

	//mrb_top_self 함수는  mrb_obj_value(mrb->top_self);와 같습니다.

	auto return_value = mrb_funcall_argv(mrb, top_class_value, function_symbol, 2, params);
	std::cout << "get function return value:" << return_value.value.i << std::endl;

	puts("end of the era!");

	mrb_close(mrb);
} 

void load_file_and_make_class()
{
	auto mrb = get_state();
	if (!mrb) { return;  }

	FILE* file = nullptr;
	fopen_s(&file, "test.rb", "rt");

	puts("load_file_and_make_class");

	if (!file) {
		puts("FILE NULL");
		return; 
	}

	mrb_load_file(mrb, file); 
	auto test_inst = mrb_class_new_instance(mrb, 0, nullptr, mrb_class_get(mrb, "Test"));

	mrb_value params[2]; //x, y 포지션.

	params[0] = mrb_fixnum_value(10);
	params[1] = mrb_fixnum_value(10);

	mrb_funcall_argv(mrb, test_inst, mrb_intern_cstr(mrb, "move_to"), 2, params); 

	mrb_close(mrb);
}
