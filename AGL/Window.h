#pragma once 
#include"dtl.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

extern bool Im_debug;

namespace GL
{
	class Window
	{
	private:
		bool m_isIGused;
		bool m_doIcone;
		GLFWwindow* m_ID;
		int m_w, m_h;
		std::string m_t;
		GLFWmonitor* m_moni;
	public:
		Window(const Window&) = delete;
		Window(int width, int height, std::string title, GLFWmonitor* monitor = NULL);
		~Window();
		void Create(bool Maximised = false, bool Resizible = true);
		bool CloseCallBack();
		void Close();
		void FEP();
		void SetIcone(const std::string& icon, const std::string& icon_small);
		GLFWwindow* PassPointer();
		bool getButtonPressed(int key);
		glm::vec2 GetWindowSize();
		//std::string OpenFileDialogeBox(const char* filter = "");
		//std::string SaveFileDialogeBox(const char* filter = "");
	};
}

