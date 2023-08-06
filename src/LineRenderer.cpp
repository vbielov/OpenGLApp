#include "LineRenderer.hpp"

unsigned int LineRenderer::VBO = 0;
unsigned int LineRenderer::VAO = 0;
unsigned int LineRenderer::EBO = 0;

unsigned int LineRenderer::vertexCount = 0;

Shader* LineRenderer::shader = nullptr;

LineRenderer::LineRenderer()
{
	// VBO
	glGenBuffers(1, &VBO);  
	const int allocateVerticies = 64000;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  
	glBufferData(GL_ARRAY_BUFFER, allocateVerticies * sizeof(LineVertex), NULL, GL_DYNAMIC_DRAW);

	// VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

	// VAO: pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)0);
	glEnableVertexAttribArray(0);  

	// VAO: color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

    LineRenderer::shader = new Shader("/home/user/Desktop/dev/OpenGLApp/res/lineShader.glsl");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

LineRenderer::~LineRenderer()
{
    delete LineRenderer::shader;
}

void LineRenderer::DrawLine(LineVertex start, LineVertex end)
{
    LineVertex vertices[2] = {
        start, end
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, LineRenderer::vertexCount * sizeof(LineVertex), 2 * sizeof(LineVertex), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	LineRenderer::vertexCount += 2;
}

void LineRenderer::DrawCall()
{
    if(LineRenderer::vertexCount == 0)
		return;
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    shader->Use();
    shader->SendMatrix("u_Projection", Window::projectionMatrix);

    glDrawArrays(GL_LINES, 0, LineRenderer::vertexCount);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    LineRenderer::vertexCount = 0;
}
