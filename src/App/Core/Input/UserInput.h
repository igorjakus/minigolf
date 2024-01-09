// UserInput.h 
//
// This class is responsible for providing user input in the application

#include <Window.h>

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
	bool isKeyClicked(const std::string& key);

	std::pair<float, float> getMousePos() const;
	float getMouseX() const;
	float getMouseY() const;

	bool isLeftMousePressed() const;
	bool isLeftMouseClicked();
	bool isRightMousePressed() const;
	bool isRightMouseClicked();
	bool isMiddleMousePressed() const;
	bool isMiddleMouseClicked();

	void toggleMouseVisibility();
	void setMouseVisibility(bool visible);
	bool isMouseVisible() const;

	void toggleMousePosLock();
	void setMousePosLock(bool lock);
	bool isMouseLocked() const;

	std::pair<float, float> getMouseOffset() const;
	float getMouseOffsetX() const;
	float getMouseOffsetY() const;

	void setCustomCursor();

	float getWheelOffset() const;

	bool isFocused() const;

	void setTargetWindow(const agl::Window& window);
	void frameEnd();

private:

	void updateMouseState();

	struct KeyPair {
		int keyCode;
		bool wasPressed;
	};

	GLFWwindow* m_window;

	std::unordered_map<std::string, KeyPair> m_keys;

	bool m_LmbWasPressed = false;
	bool m_RmbWasPressed = false;
	bool m_MmbWasPressed = false;

	bool m_mouseVisible = true;
	bool m_mouseLocked = false;

	std::pair<float, float> m_prevMousePos;

	GLFWcursor* m_customCursor;

	double m_scrollOffset = 0.0;

	static Input* s_instance; //NOLINT
	// static void s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	// static void s_mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	// static void s_mouseCallback(GLFWwindow* window, int buttom, int action, int mods);
	static void s_scrollCallback(GLFWwindow* window, double	xOffset, double yOffset);
	// static void s_focusCallback(GLFWwindow* window, int focused);

	void setKeys();

};


}