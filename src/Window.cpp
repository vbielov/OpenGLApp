#include "Window.hpp"

float Window::deltaTime = 0.0f;
int Window::windowWidth = 0;
int Window::windowHeight = 0;
glm::mat4 Window::projectionMatrix;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    // Ensure the viewport covers the entire window
    glViewport(0, 0, width, height);
	Window::windowWidth = width;
	Window::windowHeight = height;
}

Window::Window(const int width, const int height, const char *title)
    : window(nullptr), lastFrame(0.0f)
{
    if (!glfwInit())
	{
		std::cout << "GLFW Init failed!" << std::endl;
		return;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		std::cout << "Window creation failed!" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// I need to sort them anyway. There is no point in depth testing...
	// glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_LESS);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return;
	}

	glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    std::cout << "OpenGL version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION)) << std::endl;

	Input::SetWindow(window);

	Window::windowWidth = width;
	Window::windowHeight = height;
	UpdateProjection();
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::IsOpen()
{
    if(glfwWindowShouldClose(window))
        return false;

    float currentFrame = glfwGetTime();
    Window::deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

	Input::UpdateOnFrame();

	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << error << std::endl;
	}

	UpdateProjection();

    glfwSwapBuffers(window);
    glfwPollEvents();
	
    return true;
}

void Window::UpdateProjection()
{
	float aspectRatio = (float)Window::windowWidth / (float)Window::windowHeight;
	float scale = 2.0f;
	float left = -aspectRatio * scale;
	float right = aspectRatio * scale;
	float bottom = -1.0f * scale;
	float top = 1.0f * scale;

	Window::projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}
