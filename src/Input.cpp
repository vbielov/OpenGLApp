#include "Input.hpp"

GLFWwindow* Input::window = nullptr;
std::unordered_map<int, int> Input::keyStateCache;
Vector2 Input::mousePosition = Vector2(0, 0);
Vector2 Input::mouseWorldPosition = Vector2(0, 0);
int Input::leftMouseCache = 0;
int Input::rightMouseCache = 0;

bool Input::GetKeyDown(int key)
{
    auto it = keyStateCache.find(key);
    if (it != keyStateCache.end()) 
    {
        return it->second == GLFW_PRESS || it->second == GLFW_REPEAT;
    }
    return false;
}

bool Input::GetMouseButtonDown(int key)
{
    if(key == 0)
        return leftMouseCache == GLFW_PRESS;
    else if(key == 1)
        return rightMouseCache == GLFW_PRESS;
    return false;
}

void Input::UpdateOnFrame()
{
    // Caching keys
    keyStateCache.clear();
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) 
    {
        keyStateCache[key] = glfwGetKey(window, key);
    }

    // Caching mouse 
    // NOTE: glfwGetMouseButton returns only press or release, I implemented repeat myself.
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        leftMouseCache = leftMouseCache == GLFW_PRESS || leftMouseCache == GLFW_REPEAT ? leftMouseCache = GLFW_REPEAT : GLFW_PRESS;
    else
        leftMouseCache = GLFW_RELEASE;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        rightMouseCache = rightMouseCache == GLFW_PRESS || rightMouseCache == GLFW_REPEAT ? rightMouseCache = GLFW_REPEAT : GLFW_PRESS;
    else
        rightMouseCache = GLFW_RELEASE;

    // Storing mousePosition
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    mousePosition = Vector2(xpos, ypos);

    // Calculating mouseWorldPosition
    Vector2 cursorPos = Vector2(
        (mousePosition.x / Window::windowWidth) * 2.0f - 1.0f,
        (1.0f - mousePosition.y / Window::windowHeight) * 2.0f - 1.0f
    );
    glm::vec4 glmCursorWorldPos = glm::vec4(cursorPos.x, cursorPos.y, 0.0f, 1.0f) / Window::projectionMatrix;
    mouseWorldPosition = Vector2(glmCursorWorldPos.x, glmCursorWorldPos.y);
}

void Input::SetWindow(GLFWwindow *window)
{
    Input::window = window;
}
