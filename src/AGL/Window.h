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
		void create();
		bool closeCallBack();
		void close();
		void setFullscreen(bool fullscreen);
		//Not fully working as indended WIP
		void setBorderless(bool borderless);
		void setVSync(bool vsync);
		void setWindowSize(uint32_t width, uint32_t height);
		void setWindowPos(uint32_t x, uint32_t y);
		void setSizeLimits(uint32_t minW, uint32_t minH, uint32_t maxW, uint32_t maxH);
		void setTitle(std::string title);
		void setIcon(std::string icon, std::string icon_small);
		void setIcon();
		void maximizeWindow(bool maximize);
		void setResizable(bool resizable);
		bool isBorderless();
		bool isFullscreen();
		std::string getTitle();
		void getWindowSize(int &width, int &height);
		void getWindowPos(int &x, int &y);
		void getScreenResolution(int& width, int& height);
		bool getVSync();
		void FEP();
		GLFWwindow* passPointer();
		//temp
		bool IsKeyPressed(int key);
	};
}
