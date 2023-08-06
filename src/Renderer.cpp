#include "Renderer.hpp"

unsigned int Renderer::VBO = 0;
unsigned int Renderer::VAO = 0;
unsigned int Renderer::EBO = 0;

unsigned int Renderer::vertexCount = 0;
unsigned int Renderer::indexCount = 0;
Material* Renderer::lastMaterial = nullptr;

Renderer::Renderer()
{
	// VBO
	glGenBuffers(1, &VBO);  
	const int allocateVerticies = 64000;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  
	glBufferData(GL_ARRAY_BUFFER, allocateVerticies * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

	// VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

	// VAO: pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);  

	// VAO: uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// VAO: color
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// EBO
	const int allocateIndicies = 96000;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, allocateIndicies * sizeof(GLuint), NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::DrawMesh(Mesh& mesh)
{
	if(mesh.vertexCount == 0 || mesh.indexCount == 0)
		return;
		
	if(Renderer::lastMaterial != nullptr && Renderer::lastMaterial != mesh.material)
		DrawCall();
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferSubData(GL_ARRAY_BUFFER, Renderer::vertexCount * sizeof(Vertex), mesh.vertexCount * sizeof(Vertex), mesh.vertexData);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, Renderer::indexCount * sizeof(GLuint), mesh.indexCount * sizeof(GLuint), mesh.indices);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Renderer::vertexCount += mesh.vertexCount;
	Renderer::indexCount += mesh.indexCount;
	Renderer::lastMaterial = mesh.material;
}

void Renderer::DrawCall()
{
	if(Renderer::indexCount == 0 || Renderer::vertexCount == 0)
		return;

	Shader* shader = Renderer::lastMaterial->shader;
	shader->Use();
	Renderer::lastMaterial->albedoTexture->Bind(0);

	shader->SendUniformSampler2D("u_Texture", 0);
	shader->SendMatrix("u_Projection", Window::projectionMatrix);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
    glDrawElements(GL_TRIANGLES, Renderer::indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Renderer::vertexCount = 0;
	Renderer::indexCount = 0;
	Renderer::lastMaterial = nullptr;
}
