// UserInput.h 
//
// Wrapper class to access glfw information about user's input.

#include "Window.h"

namespace golf {


class Input {
public:

	void setTargetWindow(const agl::Window& window);

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	GLFWwindow* m_window;
	
};


}
