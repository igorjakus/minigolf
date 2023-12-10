#include"pch.h"
#include"Window.h"
#include<stb_image.h>

GL::Window::Window(int width, int height, std::string title)
	:m_doIcone(false), m_IsVSync(true), m_ID(nullptr), m_title(title), m_monitor(nullptr), m_icone{0, 0}, m_winPos(0, 0), m_winSize(width, height) {}

GL::Window::~Window()
{ glfwDestroyWindow(m_ID); }

void GL::Window::Create(bool Maximised, bool fullscreen, bool Resizible)
{
	m_monitor = glfwGetPrimaryMonitor();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_MAXIMIZED, Maximised);
	glfwWindowHint(GLFW_RESIZABLE, Resizible);
	m_ID = glfwCreateWindow(m_winSize.x, m_winSize.y, m_title.c_str(), NULL, NULL);
	if (!m_ID)
	{
		DTL_ERR("Error with creation of a window named \"{0}\".", m_title);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_ID);
	// vsync on by default!
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DTL_ERR("Failed to initialize GLAD.");
		exit(EXIT_FAILURE);
	}
	SetFullscreen(fullscreen);
}

bool GL::Window::CloseCallBack()
{
	if (!m_ID) return false;
	return !glfwWindowShouldClose(m_ID);
}

void GL::Window::Close()
{ if (m_ID == nullptr) { return; } glfwSetWindowShouldClose(m_ID, GLFW_TRUE); }

void GL::Window::SetFullscreen(bool fullscreen)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set fullscreen."); return; }
	if (IsFullscreen() == fullscreen) return;
	if (fullscreen)
	{
		glfwGetWindowPos(m_ID, &m_winPos.x, &m_winPos.y);
		glfwGetWindowSize(m_ID, &m_winSize.x, &m_winSize.y);
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		glfwSetWindowMonitor(m_ID, m_monitor, 0, 0, mode->width, mode->height, 0);
	}
	else
	{ glfwSetWindowMonitor(m_ID, nullptr, m_winPos.x, m_winPos.y, m_winSize.x, m_winSize.y, 0); }
}

void GL::Window::SetVSync(bool vsync)
{ glfwSwapInterval(vsync); }

void GL::Window::SetWindowSize(int width, int height)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set size."); return; }
	glfwSetWindowSize(m_ID, width, height);
}

void GL::Window::SetWindowPos(int x, int y)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set position."); return; }
	glfwSetWindowPos(m_ID, x, y);
}

void GL::Window::SetSizeLimits(int minW, int minH, int maxW, int maxH)
{ 
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set size limits."); return; }
	glfwSetWindowSizeLimits(m_ID, minW, minH, maxW, maxH); 
}

void GL::Window::SetTitle(std::string title)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set a title."); return; }
	glfwSetWindowTitle(m_ID, title.c_str());
	m_title = title;
}

void GL::Window::FEP()
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before setting a frame end point."); return; }
	glfwSwapBuffers(m_ID);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
}

void GL::Window::SetIcon(std::string icon, std::string icon_small)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set an icon."); return; }

	stbi_set_flip_vertically_on_load(0);
	m_icone[0].pixels = stbi_load(icon.c_str(), &m_icone[0].width, &m_icone[0].height, 0, 4);
	m_icone[1].pixels = stbi_load(icon.c_str(), &m_icone[1].width, &m_icone[1].height, 0, 4);

	if (m_icone[0].pixels == nullptr || m_icone[1].pixels == nullptr)
	{ DTL_ERR("Failed to load window icon."); return; }

	glfwSetWindowIcon(m_ID, 2, m_icone);
	stbi_image_free(m_icone[0].pixels);
	stbi_image_free(m_icone[1].pixels);
	stbi_set_flip_vertically_on_load(1);
}

bool GL::Window::IsFullscreen()
{ return (m_ID == nullptr) ? false : glfwGetWindowMonitor(m_ID) != nullptr; }

std::string GL::Window::GetTitle()
{ return m_title; }

glm::ivec2 GL::Window::GetWindowSize()
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get window size."); return {0, 0}; }
	int w, h;
	glfwGetWindowSize(m_ID, &w, &h);
	return glm::ivec2(w, h);
}

glm::ivec2 GL::Window::GetWindowPos()
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get window position."); return { 0, 0 }; }
	int x, y;
	glfwGetWindowSize(m_ID, &x, &y);
	return glm::ivec2(x, y);
}

bool GL::Window::GetVSync()
{ return m_IsVSync; }

GLFWwindow* GL::Window::PassPointer()
{ return m_ID; }

bool GL::Window::GetButtonPressed(int key)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get button press callback."); return false; }
	return glfwGetKey(m_ID, key);
}

glm::dvec2 GL::Window::GetMousePos()
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get mouse position."); return {0, 0}; }
	glm::dvec2 mPos;
	glfwGetCursorPos(m_ID, &mPos.x, &mPos.y);
	return mPos;
}

bool GL::Window::GetMouseButtonPressed(int key)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get mouse button press callback."); return false; }
	return glfwGetMouseButton(m_ID, key);
}
