#include "Shader.hpp"

Shader* Shader::spriteShader = nullptr;

Shader::Shader(const char* filePath)
    : program(0)
{
    std::ifstream t(filePath);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::string vertexShaderSource = "";
    std::string fragmentShaderSource = "";

    int shaderToWrite = GL_VERTEX_SHADER;
    for (std::string line; std::getline(buffer, line); )
    {
        if(line.find("#vertex_shader") != std::string::npos)
        {
            shaderToWrite = GL_VERTEX_SHADER;
            continue;
        }
        else if(line.find("#fragment_shader") != std::string::npos)
        {
            shaderToWrite = GL_FRAGMENT_SHADER;
            continue;
        }
        
        if(shaderToWrite == GL_VERTEX_SHADER)
            vertexShaderSource += line + '\n';
        else if(shaderToWrite == GL_FRAGMENT_SHADER)
            fragmentShaderSource += line + '\n';
    }

    unsigned int vertexShader = CompileShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glUseProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    if(program != 0)
    {
        glDeleteProgram(program);
        program = 0;
    }
}

void Shader::Use() const
{
    glUseProgram(program);
}

void Shader::SendUniformSampler2D(const char* uniformName, int unit) const
{
    glUniform1i(glGetUniformLocation(program, uniformName), unit);
}

void Shader::SendMatrix(const char* uniformName, const glm::mat4 &matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::CompileShader(const char* source, int shaderType)
{
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        std::cout << "Error: " << shaderType << " Shader compilation failed:\n" << infoLog.data() << std::endl;

        glDeleteShader(shader);
        return 0;
    }
    return shader;
}