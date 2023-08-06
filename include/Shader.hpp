#pragma once
#include "Window.hpp"
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>
#include <string>

class Shader
{
public:
    Shader(const char* filePath);
    ~Shader();
    void Use() const;
    void SendUniformSampler2D(const char* uniformName, int unit) const;
    void SendMatrix(const char* uniformName, const glm::mat4 &matrix) const;

    static Shader* spriteShader;
private:
    unsigned int program;
    unsigned int CompileShader(const char* source, int shaderType);
};