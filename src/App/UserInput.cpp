#include "UserInput.h"
#include "GLFW/glfw3.h"

namespace golf {


Input* Input::s_instance; //NOLINT

bool Input::isKeyPressed(const std::string& key) {
	auto item = m_keys.find(key);
	if(item != m_keys.end()) {
		int keyValue = item->second;
		return glfwGetKey(m_window, keyValue) == GLFW_PRESS;
	}
	DTL_WAR("Call to unknown key value: \"{0}\"", key);
	return false;
}

bool Input::isKeyClicked(const std::string& key) {
	//TODO
	return false;
}

std::pair<float, float> Input::getMousePos() {
	double xPos = 0;
	double yPos = 0;
	glfwGetCursorPos(m_window, &xPos, &yPos);
	return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

float Input::getMouseX() {
	double xPos = 0;
	double yPos = 0;
	glfwGetCursorPos(m_window, &xPos, &yPos);
	return static_cast<float>(xPos);
}

float Input::getMouseY() {
	double xPos = 0;
	double yPos = 0;
	glfwGetCursorPos(m_window, &xPos, &yPos);
	return static_cast<float>(xPos);
}

bool Input::isLeftMousePressed() {
	return glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool Input::isLeftMouseClicked() {
	return false;
}

bool Input::isRightMousePressed() {
	return glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

bool Input::isRightMouseClicked() {
	return false;
}

float Input::getWheelOffset() {
	//TODO
	return .0f;
}

bool Input::isFocused() {
	return glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_TRUE;
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
	setKeys();
}

Input::~Input() {
	s_instance = nullptr;
}

void Input::setKeys() {

	m_keys[" "] = GLFW_KEY_SPACE;

	m_keys["Q"] = GLFW_KEY_Q;
	m_keys["W"] = GLFW_KEY_W;
	m_keys["E"] = GLFW_KEY_E;
	m_keys["R"] = GLFW_KEY_R;
	m_keys["T"] = GLFW_KEY_T;
	m_keys["Y"] = GLFW_KEY_Y;
	m_keys["Y"] = GLFW_KEY_Y;
	m_keys["U"] = GLFW_KEY_U;
	m_keys["I"] = GLFW_KEY_I;
	m_keys["O"] = GLFW_KEY_O;
	m_keys["P"] = GLFW_KEY_P;

	m_keys["A"] = GLFW_KEY_A;
	m_keys["S"] = GLFW_KEY_S;
	m_keys["D"] = GLFW_KEY_D;
	m_keys["F"] = GLFW_KEY_F;
	m_keys["G"] = GLFW_KEY_G;
	m_keys["H"] = GLFW_KEY_H;
	m_keys["J"] = GLFW_KEY_J;
	m_keys["K"] = GLFW_KEY_K;
	m_keys["L"] = GLFW_KEY_L;

	m_keys["Z"] = GLFW_KEY_Z;
	m_keys["X"] = GLFW_KEY_X;
	m_keys["C"] = GLFW_KEY_C;
	m_keys["V"] = GLFW_KEY_V;
	m_keys["B"] = GLFW_KEY_B;
	m_keys["N"] = GLFW_KEY_N;
	m_keys["M"] = GLFW_KEY_M;

	m_keys["1"] = GLFW_KEY_1;
	m_keys["2"] = GLFW_KEY_2;
	m_keys["3"] = GLFW_KEY_3;
	m_keys["4"] = GLFW_KEY_4;
	m_keys["5"] = GLFW_KEY_5;
	m_keys["6"] = GLFW_KEY_6;
	m_keys["7"] = GLFW_KEY_7;
	m_keys["8"] = GLFW_KEY_8;
	m_keys["9"] = GLFW_KEY_9;
	m_keys["0"] = GLFW_KEY_0;

	m_keys["["] = GLFW_KEY_LEFT_BRACKET;
	m_keys["{"] = GLFW_KEY_LEFT_BRACKET;
	m_keys["]"] = GLFW_KEY_RIGHT_BRACKET;
	m_keys["}"] = GLFW_KEY_RIGHT_BRACKET;
	m_keys["\\"] = GLFW_KEY_BACKSLASH;
	m_keys["|"] = GLFW_KEY_BACKSLASH;

	m_keys[";"] = GLFW_KEY_SEMICOLON;
	m_keys[":"] = GLFW_KEY_SEMICOLON;
	m_keys["'"] = GLFW_KEY_APOSTROPHE;
	m_keys["\""] = GLFW_KEY_APOSTROPHE;
	m_keys[","] = GLFW_KEY_COMMA;
	m_keys["<"] = GLFW_KEY_COMMA;
	m_keys["."] = GLFW_KEY_PERIOD;
	m_keys[">"] = GLFW_KEY_PERIOD;
	m_keys["/"] = GLFW_KEY_SLASH;
	m_keys["?"] = GLFW_KEY_SLASH;

	m_keys["-"] = GLFW_KEY_MINUS;
	m_keys["_"] = GLFW_KEY_MINUS;
	m_keys["="] = GLFW_KEY_EQUAL;
	m_keys["+"] = GLFW_KEY_EQUAL;

	m_keys["`"] = GLFW_KEY_GRAVE_ACCENT;
	m_keys["~"] = GLFW_KEY_GRAVE_ACCENT;
	m_keys["ESCAPE"] = GLFW_KEY_ESCAPE;
	m_keys["TAB"] = GLFW_KEY_TAB;
	m_keys["CAPS LOCK"] = GLFW_KEY_CAPS_LOCK;
	m_keys["LEFT SHIFT"] = GLFW_KEY_LEFT_SHIFT;
	m_keys["LEFT CONTROL"] = GLFW_KEY_LEFT_CONTROL;
	m_keys["LEFT ALT"] = GLFW_KEY_LEFT_ALT;

	m_keys["BACKSPACE"] = GLFW_KEY_BACKSPACE;
	m_keys["ENTER"] = GLFW_KEY_ENTER;
	m_keys["RIGHT SHIFT"] = GLFW_KEY_RIGHT_SHIFT;
	m_keys["RIGHT CONTROL"] = GLFW_KEY_RIGHT_CONTROL;
	m_keys["RIGHT ALT"] = GLFW_KEY_RIGHT_ALT;
	
	m_keys["UP"] = GLFW_KEY_UP;
	m_keys["DOWN"] = GLFW_KEY_DOWN;
	m_keys["LEFT"] = GLFW_KEY_LEFT;
	m_keys["RIGHT"] = GLFW_KEY_RIGHT;

	m_keys["F1"] = GLFW_KEY_F1;
	m_keys["F2"] = GLFW_KEY_F2;
	m_keys["F3"] = GLFW_KEY_F3;
	m_keys["F4"] = GLFW_KEY_F4;
	m_keys["F5"] = GLFW_KEY_F5;
	m_keys["F6"] = GLFW_KEY_F6;
	m_keys["F7"] = GLFW_KEY_F7;
	m_keys["F8"] = GLFW_KEY_F8;
	m_keys["F9"] = GLFW_KEY_F9;
	m_keys["F10"] = GLFW_KEY_F10;
	m_keys["F11"] = GLFW_KEY_F11;
	m_keys["F12"] = GLFW_KEY_F12;

	m_keys["INSERT"] = GLFW_KEY_INSERT;
	m_keys["DELETE"] = GLFW_KEY_DELETE;

}


}
