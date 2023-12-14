#include"pch.h"
#include"dtl.h"

dtl::Logger dtl::Logger::s_Log;
dtl::Logger& dtl::Logger::GetInstance() { return s_Log; }
namespace dtl { dtl::Logger& Log = dtl::Logger::GetInstance(); }
void dtl::Logger::output(const std::string& text) { m_msg << text << '\n'; }
void dtl::Logger::setFile(const std::string& filePath) { m_filepath = filePath; }

bool dtl::Logger::findToken(const std::string& s, size_t* t1, size_t* t2)
{
	*t1 = s.find('{'); *t2 = s.find('}');
	return (*t2 - *t1 == 2);
}

void dtl::Logger::processToken(char c, const std::string& arg)
{
	if (c == '0') m_msg << arg;
	else if (c == 'b') { unsigned long long val; memcpy(&val, &arg, sizeof(arg)); m_msg << std::bitset<sizeof(arg) * 8>(val); }
}
void dtl::Logger::processToken(char c, const char* arg)
{
	if (c == '0') m_msg << arg;
	else if (c == 'b') { long long val; memcpy(&val, &arg, sizeof(arg)); m_msg << std::bitset<sizeof(arg) * 8>(val); }
}

void dtl::Logger::showtime()
{
	if (m_timeFormat == DTL_PROGRAM_TIME) 
	{
		long ctime = (clock() - m_time_start) / 1000;
		m_msg
			<< "[" << std::setfill('0') << std::setw(2) << (ctime / 3600) << ":"
			<< std::setw(2) << ctime % 3600 / 60 << ":" << std::setw(2) << ctime % 60 << "]"; 
	}
	else if (m_timeFormat == DTL_SYSTEM_TIME)
	{
		auto t = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		m_msg << "[" << std::setfill('0')<<
		std::setw(2) << (t / 60 / 60) % 24 << ":" <<
		std::setw(2) << (t / 60) % 60 << ":" << 
		std::setw(2) << t % 60 << "]";
	}
	else if (m_timeFormat == DTL_DONT_SHOW) { return; }
	else m_msg << "[ERROR]";
}

dtl::Logger::Logger()
	:m_time_start(std::clock()), m_mode(0), m_colEntry(DTL_WHITE),
	m_colInfo(DTL_GREEN), m_colWarning(DTL_YELLOW), m_colError(DTL_RED), m_timeFormat(0) {}

dtl::Logger::~Logger() 
{ 
	if (!m_msg.str().empty() && m_mode == DTL_FILE) 
	{ 
		m_outf.open(m_filepath, std::ofstream::out); 
		if (m_outf.is_open())
		{
			m_outf << m_msg.str();
			m_outf.close();
		}
	} 
}

void dtl::Logger::settings(std::string entryCol, std::string infoCol, std::string warningCol, std::string errorCol, int timeFormat, uint32_t logLocation)
{
	if (entryCol != "\0") m_colEntry = entryCol;
	if (infoCol != "\0") m_colInfo = infoCol;
	if (warningCol != "\0") m_colWarning = warningCol;
	if (errorCol != "\0") m_colError = errorCol;
	m_timeFormat = timeFormat;
	m_mode = logLocation;
}
