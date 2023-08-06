#pragma once
#include "Vector.hpp"
#include "Material.hpp"
#include "Sprite.hpp"

class Vertex
{
public:
    Vector3 pos;
    Vector2 uv;
    Vector4 color;

    Vertex() {}

    Vertex(Vector3 pos, Vector2 uv, Vector4 color)
        : pos(pos), uv(uv), color(color) {}
};

class Mesh
{
public:
    Mesh();
    ~Mesh();

    // Create mesh
    void SetCustomMesh(Vector3* vertices, Vector2* uvs, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount, Material* material);
    void SetQuadMesh(Material *material);

    // After mesh created
    void SetPosition(Vector2 position);
    void SetScale(Vector2 scale);
    void SetMaterial(Material* material);
    
    Vertex* vertexData;

    Vector3* vertices;
    Vector2* uvs;
    unsigned int* indices;

    unsigned int vertexCount;
    unsigned int indexCount;

    Material* material;
private:
    void ConstructVertexData();
    Vector2 position;
    Vector2 scale;
};