#pragma once

#include "Agl.h"
#include "Window.h"
#include <list>

namespace golf
{
class Input {

public:

Input();
	~Input();
	Input(const Input &) = delete;
	Input(Input &&) = delete;
	Input &operator=(const Input &) = delete;
	Input &operator=(Input &&) = delete;

	[[nodiscard]] bool isKeyPressed(const std::string& key) const;
	bool isKeyClicked(const std::string& key);

	[[nodiscard]] std::pair<float, float> getMousePos() const;
	[[nodiscard]] float getMouseX() const;
	[[nodiscard]] float getMouseY() const;

	[[nodiscard]] bool isLeftMousePressed() const;
	bool isLeftMouseClicked();
	[[nodiscard]] bool isRightMousePressed() const;
	bool isRightMouseClicked();
	[[nodiscard]] bool isMiddleMousePressed() const;
	bool isMiddleMouseClicked();

	void toggleMouseVisibility();
	void setMouseVisibility(bool visible);
	[[nodiscard]] bool isMouseVisible() const;

	void toggleMousePosLock();
	void setMousePosLock(bool lock);
	[[nodiscard]] bool isMouseLocked() const;

	[[nodiscard]] std::pair<float, float> getMouseOffset() const;
	[[nodiscard]] float getMouseOffsetX() const;
	[[nodiscard]] float getMouseOffsetY() const;

	void attachCamera(agl::Camera* camera, float constvalue, bool isHeight);
	void resetCameras();
	void newScene();

	void setCustomCursor();

	[[nodiscard]] float getWheelOffset() const;

	[[nodiscard]] bool isFocused() const;

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

	struct Camera {
		agl::Camera* camera;
		float constvalue;
		bool height;
	};
	std::list<Camera> m_cameras;
	std::list<size_t> m_camerasCounts;

	static Input* s_instance; //NOLINT
	// static void s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	// static void s_mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	// static void s_mouseCallback(GLFWwindow* window, int buttom, int action, int mods);
	static void s_scrollCallback(GLFWwindow* window, double	xOffset, double yOffset);
	// static void s_focusCallback(GLFWwindow* window, int focused);
	static void s_resizeCallback(GLFWwindow* window, int width, int height);

	void setKeys();

};
}
