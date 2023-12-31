// UserInput.h 
//
// Wrapper class to access glfw information about user's input.

#include "Window.h"
#include <string>

namespace golf {


class Input {

public:

	~Input();
	Input(const Input &) = delete;
	Input(Input &&) = delete;
	Input &operator=(const Input &) = delete;
	Input &operator=(Input &&) = delete;

	bool isKeyPressed(std::string key);
	bool isKeyClicked(std::string key);

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
	Input();

	GLFWwindow* m_window;

	// static constexpr size_t keysNum = 130;
	// std::array<bool, keysNum> keys;

	static Input* s_instance; //NOLINT
	static void s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void s_mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	static void s_mouseCallback(GLFWwindow* window, int buttom, int action, int mods);
	static void s_scrollCallback(GLFWwindow* window, double	xOffset, double yOffset);
	static void s_focusCallback(GLFWwindow* window, int focused);

	friend class AppData;
};


}
