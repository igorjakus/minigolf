// App.h 
// 
// the main application class 

#pragma once

#include "Window.h"

#include <string>



namespace golf {

class App {

public:
	explicit App(unsigned int width = c_defaultWidth, unsigned int height = c_defaultHeight, std::string title = c_defaultTitle);
	~App();
	App(App &&) = delete;
	App(const App &) = delete;
	App &operator=(App &&) = delete;
	App &operator=(const App &) = delete;

	void run();


private:
	void terminate();

	static constexpr unsigned int c_defaultWidth = 1080;
	static constexpr unsigned int c_defaultHeight = 720;
	static const std::string c_defaultTitle;

	agl::Window window;


};

}
