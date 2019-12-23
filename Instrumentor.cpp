#include "Instrumentor.h"
#include <algorithm>

using std::string;

const char* const indent_1_c = "\n\t";
const char* const indent_2_c = "\n\t\t";
const char* const indent_3_c = "\n\t\t\t";

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
    m_output_stream << "{";
    m_output_stream << indent_1_c << "\"otherData\": {},";
    m_output_stream << indent_1_c << "\"traceEvents\": [";
    m_output_stream.flush();
}

void Instrumentor::write_profile(const Profile_Result& result)
{
    if (1 < ++m_profile_count)
        m_output_stream << ",";

    string name = result.name;
    replace(name.begin(), name.end(), '"', '\'');

    m_output_stream << indent_2_c << "{";
    m_output_stream << indent_3_c << "\"cat\": \"function\",";
    m_output_stream << indent_3_c << "\"dur\": " << (result.end - result.start) << ',';
    m_output_stream << indent_3_c << "\"name\": \"" << name << "\",";
    m_output_stream << indent_3_c << "\"ph\": \"X\",";
    m_output_stream << indent_3_c << "\"pid\": 0,";
    m_output_stream << indent_3_c << "\"tid\": " << result.thread_ID << ',';
    m_output_stream << indent_3_c << "\"ts\": " << result.start;
    m_output_stream << indent_2_c << "}";

    m_output_stream.flush();
}

void Instrumentor::write_footer()
{
    m_output_stream << indent_1_c << "]"; 
    m_output_stream << "\n}";
    m_output_stream.flush();
}
