#pragma once 
#include"dtl.h"
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>

namespace agl
{
	class Window
	{
	private:
		bool m_isVSync;
		bool m_isBorderless;
		GLFWwindow* m_ID;
		std::string m_title;
		GLFWmonitor* m_monitor;
		GLFWimage m_icone[2];
		int m_winPosX, m_winPosY;
		int m_winSizeW, m_winSizeH;
	public:
		Window(const Window&) = delete;
		Window(uint32_t width, uint32_t height, std::string title);
		~Window();
		void Create();
		bool CloseCallBack();
		void Close();
		void SetFullscreen(bool fullscreen);
		//Not fully working as indended WIP
		void SetBorderless(bool borderless);
		void SetVSync(bool vsync);
		void SetWindowSize(uint32_t width, uint32_t height);
		void SetWindowPos(uint32_t x, uint32_t y);
		void SetSizeLimits(uint32_t minW, uint32_t minH, uint32_t maxW, uint32_t maxH);
		void SetTitle(std::string title);
		void SetIcon(std::string icon, std::string icon_small);
		void SetIcon();
		void MaximizeWindow(bool maximize);
		void SetResizable(bool resizable);
		bool IsBorderless();
		bool IsFullscreen();
		std::string GetTitle();
		void GetWindowSize(int &width, int &height);
		void GetWindowPos(int &x, int &y);
		void GetScreenResolution(int& width, int& height);
		bool GetVSync();
		void FEP();
		GLFWwindow* PassPointer();
		//temp
		bool IsKeyPressed(int key);
	};
}
