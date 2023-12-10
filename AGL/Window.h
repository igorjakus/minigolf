#pragma once 
#include"dtl.h"
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>

namespace GL
{
	class Window
	{
	private:
		bool m_doIcone;
		bool m_IsVSync;
		GLFWwindow* m_ID;
		std::string m_title;
		GLFWmonitor* m_monitor;
		GLFWimage m_icone[2];
		glm::ivec2 m_winPos;
		glm::ivec2 m_winSize;
	public:
		Window(const Window&) = delete;
		Window(int width, int height, std::string title);
		~Window();
		void Create(bool Maximised = false, bool fullscreen = false, bool Resizible = true);
		bool CloseCallBack();
		void Close();
		void SetFullscreen(bool fullscreen);
		void SetVSync(bool vsync);
		void SetWindowSize(int width, int height);
		void SetWindowPos(int x, int y);
		void SetSizeLimits(int minW, int minH, int maxW, int maxH);
		void SetTitle(std::string title);
		void SetIcon(std::string icon, std::string icon_small);
		bool IsFullscreen();
		std::string GetTitle();
		glm::ivec2 GetWindowSize();
		glm::ivec2 GetWindowPos();
		bool GetVSync();
		void FEP();
		GLFWwindow* PassPointer();
		bool GetButtonPressed(int key);
		glm::dvec2 GetMousePos();
		bool GetMouseButtonPressed(int key);
	};
}

