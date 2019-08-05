#include "stdafx.h"
#include "RubyValues.h"

mrb_value RubyValues::GetRubyFixNum(int number)
{
	return mrb_fixnum_value(number);
}