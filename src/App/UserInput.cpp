#include "UserInput.h"
#include "GLFW/glfw3.h"

namespace golf {


bool Input::isKeyPressed(std::string key) {

}

bool Input::isKeyClicked(std::string key) {

}

float Input::getMouseX() {

}

float Input::getMouseY() {

}

bool Input::isLeftMousePressed() {

}

bool Input::isLeftMouseClicked() {

}

bool Input::isRightMousePressed() {

}

bool Input::isRightMouseClicked() {

}

float Input::getWheelOffset() {

}

bool Input::isFocused() {

}

void Input::setTargetWindow(const agl::Window& window) {
	m_window = window.passPointer();

	glfwSetKeyCallback(m_window, s_keyCallback); 
	glfwSetCursorPosCallback(m_window, s_mousePosCallback);
	glfwSetMouseButtonCallback(m_window, s_mouseCallback);
	glfwSetScrollCallback(m_window, s_scrollCallback);
	glfwSetWindowFocusCallback(m_window, s_focusCallback);
}

void Input::s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { //NOLINT
	// s_instance->doSomething();
}

void Input::s_mousePosCallback(GLFWwindow* window, double xPos, double yPos) { //NOLINT

}
void Input::s_mouseCallback(GLFWwindow* window, int buttom, int action, int mods) { //NOLINT

}
void Input::s_scrollCallback(GLFWwindow* window, double	xOffset, double yOffset) { //NOLINT

}
void Input::s_focusCallback(GLFWwindow* window, int focused) { //NOLINT

}


Input::Input() 
	:m_window(nullptr) {
	s_instance = this;
}

Input::~Input() {
	s_instance = nullptr;
}


}
