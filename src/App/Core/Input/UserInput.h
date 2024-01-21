#pragma once

#include "Agl.h"
#include "Window.h"

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

	[[nodiscard]] std::pair<float, float> getMouseWorldPos(agl::Camera&) const;
	[[nodiscard]] float getMouseWorldX(agl::Camera&) const;
	[[nodiscard]] float getMouseWorldY(agl::Camera&) const;

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

	[[nodiscard]] std::pair<float, float> getMouseWorldOffset(agl::Camera&) const;
	[[nodiscard]] float getMouseWorldOffsetX(agl::Camera&) const;
	[[nodiscard]] float getMouseWorldOffsetY(agl::Camera&) const;

	void attachCamera(agl::Camera* camera, float constvalue, bool dynamic = false);
	void changeCameraSet(uint64_t setID);
	uint64_t newScene();

	void setCustomCursor();

	[[nodiscard]] float getWheelOffset() const;

	[[nodiscard]] bool isFocused() const;

	[[nodiscard]] std::pair<float, float> screenToWorld(std::pair<float, float>, agl::Camera&) const;

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
		bool dynamic;

		void updateSize(float width, float height);
	};
	struct CameraSet {
		std::vector<Camera> cameras;
		uint64_t setID;
		explicit CameraSet(uint64_t id);
	};
	std::list<std::shared_ptr<CameraSet>> m_cameraSets;
	std::list<std::shared_ptr<CameraSet>>::iterator m_currentCameraSet;
	uint64_t m_cameraSetsCount = 0;

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
