#include "Instrumentation_Timer.h"
#include <chrono>
#include <cmath>
#include <iostream>

using namespace std;

void run_funcs();
void function_1();
void function_2();

int main()
{
	Instrumentor::get_instance().begin_session("My Session");

	run_funcs();
	run_funcs();

	Instrumentor::get_instance().end_session();

	return 0;
}

void run_funcs()
{
	PROFILE_FUNCTION();
	function_1();
	function_2();
}

void function_1()
{
	PROFILE_FUNCTION();

	for (int i = 0; i < 1000; ++i)
		cout << __FUNCTION__ << ": " << i << endl;
}

void function_2()
{
	PROFILE_FUNCTION();

	for (int i = 0; i < 1000; ++i)
		cout << __FUNCTION__ << ": " << sqrt(i) << endl;
}
