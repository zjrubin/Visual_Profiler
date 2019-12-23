#include "Instrumentation_Timer.h"
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	Instrumentor::get_instance().begin_session("My Session");
	{
		Instrumentation_Timer t{ "Main" };
		std::this_thread::sleep_for(0.01s);
	}
	Instrumentor::get_instance().end_session();

	return 0;
}