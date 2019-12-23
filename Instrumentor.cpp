#include "Instrumentor.h"
#include <algorithm>

using namespace std;

Instrumentor::Instrumentor()
    : m_profile_count{ 0 }
{}

void Instrumentor::begin_session(const string& name, const string& filepath)
{
    m_output_stream.open(filepath);
    write_header();
    m_current_session = name;
}

void Instrumentor::end_session()
{
    write_footer();
    m_output_stream.close();
    m_current_session.clear();
    m_profile_count = 0;
}

void Instrumentor::write_header()
{
    m_output_stream << "{\n\t\"otherData\": {},\n\t\"traceEvents\": [\n";
    m_output_stream.flush();
}

void Instrumentor::write_profile(const Profile_Result& result)
{
    if (m_profile_count++ > 0)
        m_output_stream << ",";

    string name = result.name;
    replace(name.begin(), name.end(), '"', '\'');

    m_output_stream << "\t\t{";
    m_output_stream << "\n\t\t\t\"cat\": \"function\",";
    m_output_stream << "\n\t\t\t\"dur\": " << (result.end - result.start) << ',';
    m_output_stream << "\n\t\t\t\"name\": \"" << name << "\",";
    m_output_stream << "\n\t\t\t\"ph\": \"X\",";
    m_output_stream << "\n\t\t\t\"pid\": 0,";
    m_output_stream << "\n\t\t\t\"tid\": " << result.thread_ID << ',';
    m_output_stream << "\n\t\t\t\"ts\": " << result.start;
    m_output_stream << "\n\t\t}";

    m_output_stream.flush();
}

void Instrumentor::write_footer()
{
    m_output_stream << "\n\t]\n}";
    m_output_stream.flush();
}
