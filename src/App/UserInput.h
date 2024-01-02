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

	bool isKeyPressed(const std::string& key) const;
	bool isKeyClicked(const std::string& key) const;

	std::pair<float, float> getMousePos() const;
	float getMouseX() const;
	float getMouseY() const;
	bool isLeftMousePressed() const;
	bool isLeftMouseClicked() const;
	bool isRightMousePressed() const;
	bool isRightMouseClicked() const;

	void toggleMousePosLock() const;
	std::pair<float, float> getMousePosOffset() const;
	float getMouseXOffset() const;
	float getMouseYOffset() const;

	float getWheelOffset() const;

	bool isFocused();

	void setTargetWindow(const agl::Window& window);
	void frameEnd();

private:

	struct KeyPair {
		int keyCode;
		bool wasPressed;
	};

	GLFWwindow* m_window;

	mutable std::unordered_map<std::string, KeyPair> m_keys;

	mutable bool m_LmbWasPressed;
	mutable bool m_RmbWasPressed;

	mutable bool m_mouseLocked;

	double m_scrollOffset;

	static Input* s_instance; //NOLINT
	// static void s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	// static void s_mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	// static void s_mouseCallback(GLFWwindow* window, int buttom, int action, int mods);
	static void s_scrollCallback(GLFWwindow* window, double	xOffset, double yOffset);
	// static void s_focusCallback(GLFWwindow* window, int focused);

	void setKeys();

};


}
