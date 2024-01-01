// UserInput.h 
//
// Wrapper class to access glfw information about user's input.

#include "Window.h"
#include <string>
#include <unordered_map>

namespace golf {


class Input {

public:

	Input();
	~Input();
	Input(const Input &) = delete;
	Input(Input &&) = delete;
	Input &operator=(const Input &) = delete;
	Input &operator=(Input &&) = delete;

	bool isKeyPressed(const std::string& key);
	bool isKeyClicked(const std::string& key);

	std::pair<float, float> getMousePos();
	float getMouseX();
	float getMouseY();
	bool isLeftMousePressed();
	bool isLeftMouseClicked();
	bool isRightMousePressed();
	bool isRightMouseClicked();

	float getWheelOffset();

	bool isFocused();

	void setTargetWindow(const agl::Window& window);

private:

	GLFWwindow* m_window;

	std::unordered_map<std::string, int> m_keys;

	static Input* s_instance; //NOLINT
	static void s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void s_mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	static void s_mouseCallback(GLFWwindow* window, int buttom, int action, int mods);
	static void s_scrollCallback(GLFWwindow* window, double	xOffset, double yOffset);
	static void s_focusCallback(GLFWwindow* window, int focused);

	void setKeys();

};


}
