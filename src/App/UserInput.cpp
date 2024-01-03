#include "UserInput.h"
#include "GLFW/glfw3.h"

namespace golf {


Input* Input::s_instance; //NOLINT

//////////////////////////////////////////////
///				Keyboard Input
//////////////////////////////////////////////

bool Input::isKeyPressed(const std::string& key) const {
	auto item = m_keys.find(key);
	if(item != m_keys.end()) {
		int keyValue = item->second.keyCode;
		return glfwGetKey(m_window, keyValue) == GLFW_PRESS;
	}
	DTL_WAR("Call to unknown key value: \"{0}\"", key);
	return false;
}

bool Input::isKeyClicked(const std::string& key) {
	auto item = m_keys.find(key);
	if(item != m_keys.end()) {
		int keyValue = item->second.keyCode;
		bool pressedNow = glfwGetKey(m_window, keyValue) == GLFW_PRESS;
		bool result = !item->second.wasPressed && pressedNow;
		item->second.wasPressed = pressedNow;
		return result;
	}
	DTL_WAR("Call to unknown key value: \"{0}\"", key);
	return false;
}

//////////////////////////////////////////////
///				Mouse Input	
//////////////////////////////////////////////

std::pair<float, float> Input::getMousePos() const {
	double xPos = 0;
	double yPos = 0;
	glfwGetCursorPos(m_window, &xPos, &yPos);
	return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

float Input::getMouseX() const {
	double xPos = 0;
	double yPos = 0;
	glfwGetCursorPos(m_window, &xPos, &yPos);
	return static_cast<float>(xPos);
}

float Input::getMouseY() const {
	double xPos = 0;
	double yPos = 0;
	glfwGetCursorPos(m_window, &xPos, &yPos);
	return static_cast<float>(yPos);
}

bool Input::isLeftMousePressed() const {
	return glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool Input::isLeftMouseClicked() {
	bool pressedNow = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS; 
	bool result = !m_LmbWasPressed && pressedNow;
	m_LmbWasPressed = pressedNow;
	return result;
}

bool Input::isRightMousePressed() const {
	return glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

bool Input::isRightMouseClicked() {
	bool pressedNow = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS; 
	bool result = !m_RmbWasPressed && pressedNow;
	m_RmbWasPressed = pressedNow;
	return result;
}

bool Input::isMiddleMousePressed() const {
	return glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
}

bool Input::isMiddleMouseClicked() {
	bool pressedNow = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS; 
	bool result = !m_MmbWasPressed && pressedNow;
	m_MmbWasPressed = pressedNow;
	return result;
}

//////////////////////////////////////////////
///			Mouse Options Control	
//////////////////////////////////////////////

void Input::toggleMouseVisibility() {
	if(!m_mouseLocked) {
		m_mouseVisible = !m_mouseVisible;
		glfwSetInputMode(m_window, GLFW_CURSOR, m_mouseVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
	}
}

void Input::setMouseVisibility(bool visible) {
	if(visible != m_mouseVisible) {
		toggleMouseVisibility();
	}
}

bool Input::isMouseVisible() const {
	return m_mouseVisible;
}

void Input::toggleMousePosLock() {
	m_mouseLocked = !m_mouseLocked;
	m_mouseVisible = true;
	if(m_mouseLocked) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if(glfwRawMouseMotionSupported() == GLFW_TRUE) {
			glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		m_prevMousePos = getMousePos();
	} else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if(glfwRawMouseMotionSupported() == GLFW_TRUE) {
			glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}
	}
}

void Input::setMousePosLock(bool lock) {
	if(lock != m_mouseLocked) {
		toggleMousePosLock();
	}
}

bool Input::isMouseLocked() const {
	return m_mouseLocked;
}

//////////////////////////////////////////////
///				Locked Mouse Mode	
//////////////////////////////////////////////

std::pair<float, float> Input::getMouseOffset() const {
	auto[xPos, yPos] = getMousePos();
	xPos -= m_prevMousePos.first;
	yPos -= m_prevMousePos.second;
	return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

float Input::getMouseOffsetX() const {
	float xPos = getMouseX();
	xPos -= m_prevMousePos.first;
	return static_cast<float>(xPos);
}

float Input::getMouseOffsetY() const {
	float yPos = getMouseX();
	yPos -= m_prevMousePos.second;
	return static_cast<float>(yPos);
}

//////////////////////////////////////////////
///					Other	
//////////////////////////////////////////////

float Input::getWheelOffset() const {
	return static_cast<float>(m_scrollOffset);
}

bool Input::isFocused() const {
	return glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_TRUE;
}

//////////////////////////////////////////////
///				Technical Methods	
//////////////////////////////////////////////

void Input::setTargetWindow(const agl::Window& window) {
	m_window = window.passPointer();

	// glfwSetKeyCallback(m_window, s_keyCallback); 
	// glfwSetCursorPosCallback(m_window, s_mousePosCallback);
	// glfwSetMouseButtonCallback(m_window, s_mouseCallback);
	glfwSetScrollCallback(m_window, s_scrollCallback);
	// glfwSetWindowFocusCallback(m_window, s_focusCallback);
}

void Input::frameEnd() {
	m_scrollOffset = 0.0;
}

// void Input::s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { //NOLINT
//
// }
//
// void Input::s_mousePosCallback(GLFWwindow* window, double xPos, double yPos) { //NOLINT
//
// }
// void Input::s_mouseCallback(GLFWwindow* window, int buttom, int action, int mods) { //NOLINT
//
// }
void Input::s_scrollCallback([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double xOffset, double yOffset) { //NOLINT
	s_instance->m_scrollOffset += yOffset;
}
// void Input::s_focusCallback(GLFWwindow* window, int focused) { //NOLINT
//
// }

Input::Input() 
	:m_window(nullptr) {
	s_instance = this;
	setKeys();
}

Input::~Input() {
	s_instance = nullptr;
}

void Input::setKeys() {

	m_keys[" "] = {GLFW_KEY_SPACE, false};
	m_keys["SPACE"] = {GLFW_KEY_SPACE, false};

	m_keys["Q"] = {GLFW_KEY_Q, false};
	m_keys["W"] = {GLFW_KEY_W, false};
	m_keys["E"] = {GLFW_KEY_E, false};
	m_keys["R"] = {GLFW_KEY_R, false};
	m_keys["T"] = {GLFW_KEY_T, false};
	m_keys["Y"] = {GLFW_KEY_Y, false};
	m_keys["Y"] = {GLFW_KEY_Y, false};
	m_keys["U"] = {GLFW_KEY_U, false};
	m_keys["I"] = {GLFW_KEY_I, false};
	m_keys["O"] = {GLFW_KEY_O, false};
	m_keys["P"] = {GLFW_KEY_P, false};

	m_keys["A"] = {GLFW_KEY_A, false};
	m_keys["S"] = {GLFW_KEY_S, false};
	m_keys["D"] = {GLFW_KEY_D, false};
	m_keys["F"] = {GLFW_KEY_F, false};
	m_keys["G"] = {GLFW_KEY_G, false};
	m_keys["H"] = {GLFW_KEY_H, false};
	m_keys["J"] = {GLFW_KEY_J, false};
	m_keys["K"] = {GLFW_KEY_K, false};
	m_keys["L"] = {GLFW_KEY_L, false};

	m_keys["Z"] = {GLFW_KEY_Z, false};
	m_keys["X"] = {GLFW_KEY_X, false};
	m_keys["C"] = {GLFW_KEY_C, false};
	m_keys["V"] = {GLFW_KEY_V, false};
	m_keys["B"] = {GLFW_KEY_B, false};
	m_keys["N"] = {GLFW_KEY_N, false};
	m_keys["M"] = {GLFW_KEY_M, false};

	m_keys["1"] = {GLFW_KEY_1, false};
	m_keys["2"] = {GLFW_KEY_2, false};
	m_keys["3"] = {GLFW_KEY_3, false};
	m_keys["4"] = {GLFW_KEY_4, false};
	m_keys["5"] = {GLFW_KEY_5, false};
	m_keys["6"] = {GLFW_KEY_6, false};
	m_keys["7"] = {GLFW_KEY_7, false};
	m_keys["8"] = {GLFW_KEY_8, false};
	m_keys["9"] = {GLFW_KEY_9, false};
	m_keys["0"] = {GLFW_KEY_0, false};

	m_keys["["] = {GLFW_KEY_LEFT_BRACKET, false};
	m_keys["{"] = {GLFW_KEY_LEFT_BRACKET, false};
	m_keys["]"] = {GLFW_KEY_RIGHT_BRACKET, false};
	m_keys["}"] = {GLFW_KEY_RIGHT_BRACKET, false};
	m_keys["\\"] = {GLFW_KEY_BACKSLASH, false};
	m_keys["|"] = {GLFW_KEY_BACKSLASH, false};

	m_keys[";"] = {GLFW_KEY_SEMICOLON, false};
	m_keys[":"] = {GLFW_KEY_SEMICOLON, false};
	m_keys["'"] = {GLFW_KEY_APOSTROPHE, false};
	m_keys["\""] = {GLFW_KEY_APOSTROPHE, false};
	m_keys[","] = {GLFW_KEY_COMMA, false};
	m_keys["<"] = {GLFW_KEY_COMMA, false};
	m_keys["."] = {GLFW_KEY_PERIOD, false};
	m_keys[">"] = {GLFW_KEY_PERIOD, false};
	m_keys["/"] = {GLFW_KEY_SLASH, false};
	m_keys["?"] = {GLFW_KEY_SLASH, false};

	m_keys["-"] = {GLFW_KEY_MINUS, false};
	m_keys["_"] = {GLFW_KEY_MINUS, false};
	m_keys["="] = {GLFW_KEY_EQUAL, false};
	m_keys["+"] = {GLFW_KEY_EQUAL, false};

	m_keys["`"] = {GLFW_KEY_GRAVE_ACCENT, false};
	m_keys["~"] = {GLFW_KEY_GRAVE_ACCENT, false};
	m_keys["ESCAPE"] = {GLFW_KEY_ESCAPE, false};
	m_keys["TAB"] = {GLFW_KEY_TAB, false};
	m_keys["CAPS LOCK"] = {GLFW_KEY_CAPS_LOCK, false};
	m_keys["LEFT SHIFT"] = {GLFW_KEY_LEFT_SHIFT, false};
	m_keys["LEFT CONTROL"] = {GLFW_KEY_LEFT_CONTROL, false};
	m_keys["LEFT ALT"] = {GLFW_KEY_LEFT_ALT, false};

	m_keys["BACKSPACE"] = {GLFW_KEY_BACKSPACE, false};
	m_keys["ENTER"] = {GLFW_KEY_ENTER, false};
	m_keys["RIGHT SHIFT"] = {GLFW_KEY_RIGHT_SHIFT, false};
	m_keys["RIGHT CONTROL"] = {GLFW_KEY_RIGHT_CONTROL, false};
	m_keys["RIGHT ALT"] = {GLFW_KEY_RIGHT_ALT, false};
	
	m_keys["UP"] = {GLFW_KEY_UP, false};
	m_keys["DOWN"] = {GLFW_KEY_DOWN, false};
	m_keys["LEFT"] = {GLFW_KEY_LEFT, false};
	m_keys["RIGHT"] = {GLFW_KEY_RIGHT, false};

	m_keys["F1"] = {GLFW_KEY_F1, false};
	m_keys["F2"] = {GLFW_KEY_F2, false};
	m_keys["F3"] = {GLFW_KEY_F3, false};
	m_keys["F4"] = {GLFW_KEY_F4, false};
	m_keys["F5"] = {GLFW_KEY_F5, false};
	m_keys["F6"] = {GLFW_KEY_F6, false};
	m_keys["F7"] = {GLFW_KEY_F7, false};
	m_keys["F8"] = {GLFW_KEY_F8, false};
	m_keys["F9"] = {GLFW_KEY_F9, false};
	m_keys["F10"] = {GLFW_KEY_F10, false};
	m_keys["F11"] = {GLFW_KEY_F11, false};
	m_keys["F12"] = {GLFW_KEY_F12, false};

	m_keys["INSERT"] = {GLFW_KEY_INSERT, false};
	m_keys["DELETE"] = {GLFW_KEY_DELETE, false};

}


}
