#pragma once
#include "Window.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include <vector>

class Renderer
{
public:
    Renderer();
    static void DrawMesh(Mesh& mesh);
    static void DrawCall();
private:
    static unsigned int VBO;
    static unsigned int VAO;
    static unsigned int EBO;

    static unsigned int vertexCount;
    static unsigned int indexCount;
    static Material* lastMaterial;
};