#include"pch.h"
#include"Window.h"
#include<GLFW/glfw3native.h>

GL::Window::Window(int width, int height, std::string title, GLFWmonitor* monitor)
	:m_isIGused(false),m_doIcone(false), m_ID(nullptr), m_w(width), m_h(height), m_t(title), m_moni(monitor)
{}

GL::Window::~Window()
{
	glfwDestroyWindow(m_ID);
}

void GL::Window::Create(bool Maximised, bool Resizible)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_MAXIMIZED, Maximised);
	glfwWindowHint(GLFW_RESIZABLE, Resizible);
	m_ID = glfwCreateWindow(m_w, m_h, m_t.c_str(), m_moni, NULL);
	if (!m_ID)
	{
		dtl::Log.error("Error with creation of a window named \"{0}\"", m_t);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_ID);
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		dtl::Log.error("Failed to initialize GLAD");
		exit(EXIT_FAILURE);
	}
}

bool GL::Window::CloseCallBack()
{
	if (!m_ID) return false;
	return !glfwWindowShouldClose(m_ID);
}

void GL::Window::Close()
{
	glfwSetWindowShouldClose(m_ID, GLFW_TRUE);
}

void GL::Window::FEP()
{
	glfwSwapBuffers(m_ID);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
}

void GL::Window::SetIcone(const std::string& icon, const std::string& icon_small)
{
	//TODO Icon image loading!!
}

GLFWwindow* GL::Window::PassPointer()
{
	return m_ID;
}


glm::vec2 GL::Window::GetWindowSize()
{
	int w, h;
	glfwGetWindowSize(m_ID, &w, &h);
	return glm::vec2(w, h);
}

bool GL::Window::getButtonPressed(int key)
{
	return glfwGetKey(m_ID, key);
}