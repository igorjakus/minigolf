// UserInput.h 
//
// Wrapper class to access glfw information about user's input.

#include "Window.h"

namespace golf {


class Input {
public:
	static Input& getInstance();

	void setTargetWindow(std::shared_ptr<agl::Window> window);

	Input(Input &&) = delete;
	Input(const Input &) = delete;
	Input &operator=(Input &&) = delete;
	Input &operator=(const Input &) = delete;

private:
	Input();
	~Input() = default;

	std::weak_ptr<agl::Window> m_window;
	
};


}
