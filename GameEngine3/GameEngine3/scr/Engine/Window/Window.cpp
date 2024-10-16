#include <Engine/Window/Window.h>

#define GLEW_STATIC
#include <GL/glew.h>
#pragma comment(lib, "OpenGl32.lib")
#pragma comment(lib, "glew32s.lib")

#include <GLFW/glfw3.h>
#pragma comment(lib, "glfw3-s.lib")

#include <stdexcept>

struct Window::Internal
{
	GLFWwindow* window;

	int width, height;
	const char* title;
};

Window::Window(const char* title, int w, int h)
	: m_window(new Internal())
{
	m_window->width = w;
	m_window->height = h;
	m_window->title = title;

	glfwInit();

	// Set context as OpenGL 4.6 Core, forward compat, with debug depending on build config
	glfwWindowHint(GLFW_CLIENT_API,				GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,	4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,	6);
	glfwWindowHint(GLFW_OPENGL_PROFILE,			GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,	GL_TRUE);
#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,	GL_TRUE);
#else /* !NDEBUG */
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,	GL_FALSE);
#endif /* !NDEBUG */
	glfwWindowHint(GLFW_SRGB_CAPABLE,			GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER,			GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE,				GL_FALSE);

	m_window->window = glfwCreateWindow(w, h, title, nullptr, nullptr);
	if (!m_window->window)
		throw std::runtime_error("Unable to initialize GLFW");

	glfwMakeContextCurrent(m_window->window);

	glewExperimental = true;
	auto glewResult = glewInit();
}

Window::~Window()
{
	glfwDestroyWindow(m_window->window);
}

bool Window::IsClose()
{
	return glfwWindowShouldClose(m_window->window);
}

void Window::SwapBuffer()
{
	glfwSwapBuffers(m_window->window);
}

void Window::PoolEvent()
{
	glfwPollEvents();
}

void Window::Terminate()
{
	glfwTerminate();
}

void Window::SetEnableMouse(bool enable)
{
	if (!enable)
		glfwSetInputMode(m_window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(m_window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

glm::vec2 Window::GetSize() const
{
	return glm::vec2(m_window->width, m_window->height);
}

GLFWwindow* Window::GetWindow() const 
{
	return m_window->window;
}
