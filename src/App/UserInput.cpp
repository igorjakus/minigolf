#include "UserInput.h"

namespace golf {


Input::Input() = default;

Input& Input::getInstance() {
	static Input instance;
	return instance;
}

void Input::setTargetWindow(std::shared_ptr<agl::Window> window) {
	m_window = window;
}


}
