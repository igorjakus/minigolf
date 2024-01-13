#pragma once
#include <string>

namespace golf 
{	
	class App {
	public:
		explicit App(unsigned int width = c_defaultWidth, unsigned int height = c_defaultHeight, const std::string& title = c_defaultTitle);
		~App() = default;
		App(App &&) = delete;
		App(const App &) = delete;
		App &operator=(App &&) = delete;
		App &operator=(const App &) = delete;	

		void run();	

	private:
		void update(float deltaT);
		void render();
	
		bool shouldClose();
	
		void terminate();
	
		const std::string m_title;
		const int32_t m_updatesPerSecond;
	
		static constexpr unsigned int c_defaultWidth = 1080;
		static constexpr unsigned int c_defaultHeight = 720;
		static constexpr unsigned int c_defaultUPS = 256;
		static const std::string c_defaultTitle;	
	};	
}
