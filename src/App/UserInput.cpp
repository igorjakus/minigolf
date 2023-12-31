#include "UserInput.h"
#include "GLFW/glfw3.h"

namespace golf {


void Input::setTargetWindow(const agl::Window& window) {
	m_window = window.passPointer();
	
	if(glfwGetWindowUserPointer(m_window) != nullptr) {
		DTL_ERR("User pointer już ustawiony!");
		return;
	}
	glfwSetWindowUserPointer(m_window, this);

	// glfwSetKeyCallback(m_window, keyCallback);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { //NOLINT

}

}
