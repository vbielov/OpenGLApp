#pragma once
#include "Window.hpp"
#include <unordered_map>
#include "Vector.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Input
{
public:
    static bool GetKeyDown(int key);
    static bool GetMouseButtonDown(int key);
    static void UpdateOnFrame();
    static void SetWindow(GLFWwindow* window);
    static Vector2 mousePosition;
    static Vector2 mouseWorldPosition;
private:
    static GLFWwindow* window;
    static std::unordered_map<int, int> keyStateCache;
    static int leftMouseCache;
    static int rightMouseCache;
};