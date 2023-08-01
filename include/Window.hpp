#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
    Window(const int width, const int height, const char* title);
    ~Window();
    bool IsOpen();
private:
    bool m_is_open;
    GLFWwindow* m_window;
};