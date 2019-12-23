#pragma once

#include <fstream>
#include <string> 

struct Profile_Result;

class Instrumentor
{
public:
    static Instrumentor& get_instance()
    {
        static Instrumentor instance;
        return instance;
    }

    void begin_session(const std::string& name, const std::string& filepath = "results.json");

    void end_session();

    void write_profile(const Profile_Result& result);

private:
    Instrumentor();
    ~Instrumentor()
    {}

    void write_header();
    void write_footer();

    std::string m_current_session;
    std::ofstream m_output_stream;
    int m_profile_count;
};

struct Profile_Result
{
    std::string name;
    long long int start;
    long long int end;
    uint32_t thread_ID;
};
