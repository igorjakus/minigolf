#pragma once
#include<iostream>
#include<iomanip>
#include<sstream>
#include<bitset>
#include<fstream>

#define PI 3.141592653589793
#define Euler 2.718281828459045
#define Golden_Ratio 1.618033988749894
#define uint uint32_t
#define ushort uint16_t
#define uchar uint8_t
#define ulong unsigned long
#define llong long long
#define ullong unsigned long long

#define DTL_LOG dtl::Logger::GetInstance()
#if defined __DEBUG__ || __RELEASE__
	#if defined __COMPILER_GCC__ || __COMPILER_CLANG__ || __COMPILER_CLANG_CL__
		#define DTL_ENT(text, ...) dtl::Log.entry(text __VA_OPT__(,) __VA_ARGS__)
		#define DTL_INF(text, ...) dtl::Log.info(text __VA_OPT__(,) __VA_ARGS__)
		#define DTL_WAR(text, ...) dtl::Log.warning(text __VA_OPT__(,) __VA_ARGS__)
		#define DTL_ERR(text, ...) dtl::Log.error(text __VA_OPT__(,) __VA_ARGS__)
	#elif defined __COMPILER_CL__
		#define DTL_ENT(text, ...) dtl::Log.entry(text, ## __VA_ARGS__)
		#define DTL_INF(text, ...) dtl::Log.info(text, ## __VA_ARGS__)
		#define DTL_WAR(text, ...) dtl::Log.warning(text, ## __VA_ARGS__)
		#define DTL_ERR(text, ...) dtl::Log.error(text, ## __VA_ARGS__)
	#else
		#error Compiler not supported
	#endif
#else
	#if defined __COMPILER_GCC__ || __COMPILER_CLANG__ || __COMPILER_CLANG_CL__
		#define DTL_ERR(text, ...) dtl::Log.error(text __VA_OPT__(,) __VA_ARGS__)
	#elif defined __COMPILER_CL__
		#define DTL_ERR(text, ...) dtl::Log.error(text, ## __VA_ARGS__)
	#endif
#define DTL_ENT(...)
#define DTL_INF(...)
#define DTL_WAR(...)
#endif
#define DTL_BLACK			"\033[0;30m"
#define DTL_DARK_GRAY		"\033[1;30m"
#define DTL_BLUE			"\033[0;34m"
#define DTL_LIGHT_BLUE		"\033[1;34m"
#define DTL_GREEN			"\033[0;32m"
#define DTL_LIGHT_GREEN		"\033[1;32m"
#define DTL_CYAN			"\033[0;36m"
#define DTL_LIGHT_CYAN		"\033[1;36m"
#define DTL_RED				"\033[0;31m"
#define DTL_LIGHT_RED		"\033[1;31m"
#define DTL_PURPLE			"\033[0;35m"
#define DTL_LIGHT_PURPLE	"\033[1;35m"
#define DTL_BROWN			"\033[0;33m"
#define DTL_YELLOW			"\033[1;33m"
#define DTL_LIGHT_GRAY		"\033[0;37m"
#define DTL_WHITE			"\033[1;37m"
#define DTL_DEFAULT			"\0"
#define DTL_PROGRAM_TIME	0
#define DTL_SYSTEM_TIME		1
#define DTL_DONT_SHOW		2
#define DTL_CONSOLE			0
#define DTL_FILE			1

namespace dtl
{
	class Logger
	{
		static Logger s_Log;
		clock_t m_time_start;
		uint m_mode;
		std::string m_colEntry;
		std::string m_colInfo;
		std::string m_colWarning;
		std::string m_colError;
		int m_timeFormat;
		std::string m_filepath;
		std::ofstream m_outf;
		std::stringstream m_msg;
		bool findToken(const std::string& s, size_t* t1, size_t* t2);
		template<typename T>
		void processToken(char c, const T& arg)
		{
			if (c == '0') m_msg << arg;
			else if (c == 'x') m_msg << std::uppercase << std::hex << arg << std::nouppercase << std::dec;
			else if (c == 'o') m_msg << std::oct << arg << std::dec;
			else if (c == 'i') m_msg << static_cast<int>(arg);
			else if (c == 's') m_msg << std::scientific << arg << std::defaultfloat;
			else if (c == 'b') { llong val; memcpy(&val, &arg, sizeof(T)); m_msg << std::bitset<sizeof(T) * 8>(val); }
		}
		void processToken(char c, const std::string& arg);
		void processToken(char c, const char* arg);

		void output(const std::string& text);
		template<typename T>
		void output(const std::string& text, T&& arg)
		{
			size_t t1, t2;
			if (!findToken(text, &t1, &t2))
			{
				if (t1 == std::string::npos) { m_msg << text << '\n'; return; }
				m_msg << text.substr(0, t2 + 1);
				output(text.substr(t2 + 1), std::forward<T>(arg));
				return;
			}
			m_msg << text.substr(0, t1);
			processToken(text[t1 + 1], arg);
			m_msg << text.substr(t1 + 3) << '\n';
		}
		template<typename T, typename ...Types>
		void output(const std::string& text, T&& arg, Types&& ...args)
		{
			size_t t1, t2;
			if (!findToken(text, &t1, &t2))
			{
				if (t1 == std::string::npos) { m_msg << text << '\n'; return; }
				m_msg << text.substr(0, t2 + 1);
				output(text.substr(t2 + 1), std::forward<T>(arg), std::forward<Types>(args)...);
				return; 
			} 
			m_msg << text.substr(0, t1);
			processToken(text[t1 + 1], arg);
			output(text.substr(t1 + 3), std::forward<Types>(args)...);
		}

		void showtime();
		Logger();
	public:
		Logger(const Logger&) = delete;
		~Logger();
		void settings(std::string entryCol, std::string infoCol, std::string warningCol, std::string errorCol, int timeFormat, uint32_t logLocation);
		void setFile(const std::string& filePath);
		static Logger& GetInstance();
		template<typename ...Types>
		void entry(std::string message, Types&& ... args)
		{
			if (m_mode == DTL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colEntry; }
			showtime();
			m_msg << "[ENT] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == DTL_CONSOLE) { m_msg << "\033[0m"; std::cout << m_msg.str(); }
		}
		template<typename ...Types>
		void error(std::string message, Types&& ... args)
		{
			if (m_mode == DTL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colError; }
			showtime();
			m_msg << "[ERR] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == DTL_CONSOLE) { m_msg << "\033[0m"; std::cerr << m_msg.str(); }
		}
		template<typename ...Types>
		void info(std::string message, Types&& ... args)
		{
			if (m_mode == DTL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colInfo; }
			showtime();
			m_msg << "[INF] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == DTL_CONSOLE) { m_msg << "\033[0m"; std::cout << m_msg.str(); }
		}
		template<typename ...Types>
		void warning(std::string message, Types&& ... args)
		{
			if (m_mode == DTL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colWarning; }
			showtime();
			m_msg << "[WAR] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == DTL_CONSOLE) { m_msg << "\033[0m"; std::cout << m_msg.str(); }
		}
	};
	extern dtl::Logger& Log;
}
