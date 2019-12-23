// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().begin_session("Session Name");        // Begin session 
// {
//     Instrumentation_Timer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::Get().end_session();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//
#pragma once

#include "Instrumentor.h"
#include <chrono>

#define PROFILE_SCOPE_SIG_DETAIL(name, line) Instrumentation_Timer timer_##line(name)
#define PROFILE_SCOPE_SIG(name, line) PROFILE_SCOPE_SIG_DETAIL(name, line)

#define PROFILING 1
#if PROFILING
    #define PROFILE_SCOPE(name) PROFILE_SCOPE_SIG(name, __LINE__) // Profiling on
    #define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
    #define PROFILE_SCOPE(name) // Profiling off
    #define PROFILE_FUNCTION()
#endif

class Instrumentation_Timer
{
public:
    Instrumentation_Timer(const char* name);

    ~Instrumentation_Timer();

    void stop();

private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};
