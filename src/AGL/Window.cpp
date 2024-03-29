#include<pch.h>
#include<Window.h>
#include<stb_image.h>
#include<ImGui.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ glViewport(0, 0, width, height); }

agl::Window::Window(uint32_t width, uint32_t height, std::string title)
	:m_isVSync(true), m_isBorderless(false), m_ID(nullptr), m_title(title), m_monitor(nullptr), m_icon{0, 0}, m_winPosX(0), m_winPosY(0), m_winSizeW(width), m_winSizeH(height) {}
agl::Window::~Window()
{ glfwDestroyWindow(m_ID); }

void agl::Window::create()
{
	m_monitor = glfwGetPrimaryMonitor();
	glfwWindowHint(GLFW_SAMPLES, 4);
	m_ID = glfwCreateWindow(m_winSizeW, m_winSizeH, m_title.c_str(), NULL, NULL);
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
	IMGUI_IMPLGL(m_ID);
	glfwSetFramebufferSizeCallback(m_ID, framebuffer_size_callback);
}

bool agl::Window::closeCallBack() const
{
	if (!m_ID) return false;
	return glfwWindowShouldClose(m_ID);
}

void agl::Window::close() const
{ if (m_ID == nullptr) { return; } glfwSetWindowShouldClose(m_ID, GLFW_TRUE); }

void agl::Window::setFullscreen(bool fullscreen)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set fullscreen."); return; }
	if (isFullscreen() == fullscreen) return;
	if (fullscreen)
	{
		glfwGetWindowPos(m_ID, &m_winPosX, &m_winPosY);
		glfwGetWindowSize(m_ID, &m_winSizeW, &m_winSizeH);
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		if (m_isVSync) {
			glfwSetWindowMonitor(m_ID, m_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		} else {
			glfwSetWindowMonitor(m_ID, m_monitor, 0, 0, mode->width, mode->height, 0);
		}
	}
	else
	{ glfwSetWindowMonitor(m_ID, nullptr, m_winPosX, m_winPosY, m_winSizeW, m_winSizeH, 0); }
}

void agl::Window::setBorderless(bool borderless)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set borderless."); return; }

	if (isBorderless() == borderless) return;
	if (borderless)
	{ glfwSetWindowAttrib(m_ID, GLFW_DECORATED, GLFW_FALSE); maximizeWindow(true); }
	else
	{ maximizeWindow(false); glfwSetWindowAttrib(m_ID, GLFW_DECORATED, GLFW_TRUE); }
	m_isBorderless = borderless;
}

void agl::Window::setVSync(bool vsync)
{ 
	glfwSwapInterval(vsync); 
	if (isFullscreen()) {
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		glfwSetWindowMonitor(m_ID, m_monitor, 0, 0, mode->width, mode->height, vsync ? mode->refreshRate : 0);
	}
}

void agl::Window::setWindowSize(uint32_t width, uint32_t height)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set size."); return; }
	glfwSetWindowSize(m_ID, width, height);
}

void agl::Window::setWindowSize(glm::uvec2 dims)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set size."); return; }
	glfwSetWindowSize(m_ID, dims.x, dims.y);
}

void agl::Window::setWindowPos(uint32_t x, uint32_t y)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set position."); return; }
	glfwSetWindowPos(m_ID, static_cast<int>(x), static_cast<int>(y));
}

void agl::Window::setWindowPos(glm::uvec2 pos)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set position."); return; }
	glfwSetWindowPos(m_ID, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void agl::Window::setSizeLimits(uint32_t minW, uint32_t minH, uint32_t maxW, uint32_t maxH)
{ 
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set size limits."); return; }
	glfwSetWindowSizeLimits(m_ID, static_cast<int>(minW), static_cast<int>(minH), static_cast<int>(maxW), static_cast<int>(maxH));
}

void agl::Window::setSizeLimits(glm::uvec2 minDims, glm::uvec2 maxDims)
{ 
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set size limits."); return; }
	glfwSetWindowSizeLimits(m_ID, static_cast<int>(minDims.x), static_cast<int>(minDims.y), static_cast<int>(maxDims.x), static_cast<int>(maxDims.y));
}

void agl::Window::setTitle(std::string title)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set a title."); return; }
	glfwSetWindowTitle(m_ID, title.c_str());
	m_title = title;
}

void agl::Window::FEP() const
{
	IMGUI_RENDER;
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before setting a frame end point."); return; }
	glfwSwapBuffers(m_ID);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
}

void agl::Window::setIcon(std::string icon, std::string icon_small)
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set an icon."); return; }

	stbi_set_flip_vertically_on_load(0);
	m_icon[0].pixels = stbi_load(icon.c_str(), &m_icon[0].width, &m_icon[0].height, 0, 4);
	m_icon[1].pixels = stbi_load(icon.c_str(), &m_icon[1].width, &m_icon[1].height, 0, 4);


	if (m_icon[0].pixels == nullptr || m_icon[1].pixels == nullptr)
	{ DTL_ERR("Failed to load window icon."); return; }

	glfwSetWindowIcon(m_ID, 2, m_icon);
	stbi_image_free(m_icon[0].pixels);
	stbi_image_free(m_icon[1].pixels);
	stbi_set_flip_vertically_on_load(1);
}

void agl::Window::setIcon() const
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set an icon."); return; }
	glfwSetWindowIcon(m_ID, 0, NULL);
}

void agl::Window::maximizeWindow(bool maximize) const
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set it's maximization."); return; }
	if (maximize)
	glfwMaximizeWindow(m_ID);
	else
	glfwRestoreWindow(m_ID);
}

void agl::Window::setResizable(bool resizable) const
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to set it's resizing."); return; }
	glfwSetWindowAttrib(m_ID, GLFW_RESIZABLE, resizable);
}

bool agl::Window::isBorderless() const
{ return m_isBorderless; }

bool agl::Window::isFullscreen() const
{ return (m_ID == nullptr) ? false : glfwGetWindowMonitor(m_ID) != nullptr; }

std::string agl::Window::getTitle()
{ return m_title; }

glm::uvec2 agl::Window::getWindowSize()
{
	int w, h;
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get window size."); return {}; }
	glfwGetWindowSize(m_ID, &w, &h);
	return { static_cast<uint>(w), static_cast<uint>(h) };
}

glm::ivec2 agl::Window::getWindowPos()
{
	int x, y;
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get window position."); return {}; }
	glfwGetWindowSize(m_ID, &x, &y);
	return { x, y };
}

glm::uvec2 agl::Window::getScreenResolution()
{
	if (m_ID == nullptr)
	{ DTL_ERR("Window hasn't yet been created. First create a window before trying to get screen resolution."); return {}; }
	const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
	return { static_cast<uint>(mode->width), static_cast<uint>(mode->height) };
}

bool agl::Window::getVSync() const
{ return m_isVSync; }

GLFWwindow* agl::Window::passPointer() const
{ return m_ID; }

