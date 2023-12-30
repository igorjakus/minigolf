#include "UserInput.h"

namespace golf {


void Input::setTargetWindow(const agl::Window& window) {
	m_window = window.passPointer();
	glfwSetKeyCallback(m_window, keyCallback);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

}
