#include "Window.hpp"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(const int width, const int height, const char *title)
    : m_is_open(false), m_window(nullptr)
{
    if (!glfwInit())
	{
		std::cout << "GLFW Init failed!" << std::endl;
		return;
	}

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_window)
	{
		std::cout << "Window creation failed!" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(m_window, key_callback);
    glfwSetWindowSizeCallback(m_window, window_size_callback);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return;
	}

    m_is_open = true;
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::IsOpen()
{
    if(glfwWindowShouldClose(m_window) || !m_is_open)
        return false;

    glfwSwapBuffers(m_window);
    glfwPollEvents();

    return true;
}