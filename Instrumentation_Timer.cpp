#include "Instrumentation_Timer.h"
#include <thread>

namespace this_thread = std::this_thread;
namespace chrono = std::chrono;
using std::hash;
using std::thread;

Instrumentation_Timer::Instrumentation_Timer(const char* name)
    : m_Name{ name }, m_Stopped{ false }
{
    m_StartTimepoint = chrono::high_resolution_clock::now();
}

Instrumentation_Timer::~Instrumentation_Timer()
{
    if (!m_Stopped)
        stop();
}

void Instrumentation_Timer::stop()
{
    auto endTimepoint = chrono::high_resolution_clock::now();

    long long start = chrono::time_point_cast<chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    long long end = chrono::time_point_cast<chrono::microseconds>(endTimepoint).time_since_epoch().count();

    uint32_t threadID = hash<thread::id>{}(this_thread::get_id());
    Instrumentor::get_instance().write_profile({ m_Name, start, end, threadID });

    m_Stopped = true;
}