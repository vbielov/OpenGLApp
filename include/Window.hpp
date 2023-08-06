#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window
{
public:
    Window(const int width, const int height, const char* title);
    ~Window();
    bool IsOpen();
    static float deltaTime;
    static int windowWidth;
    static int windowHeight;
    static glm::mat4 projectionMatrix;
private:
    GLFWwindow* window;
    void UpdateProjection();
    float lastFrame;
};