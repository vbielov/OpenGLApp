#pragma once
#include "Shader.hpp"
#include "Vector.hpp"
#include <vector>

struct LineVertex
{
    Vector2 pos;
    Vector3 color;
};

class LineRenderer
{
public:
    LineRenderer();
    ~LineRenderer();
    static void DrawLine(LineVertex start, LineVertex end);
    static void DrawCall();
private:
    static unsigned int VBO;
    static unsigned int VAO;
    static unsigned int EBO;

    static unsigned int vertexCount;

    static Shader* shader;
};