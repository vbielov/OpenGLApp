#include "Mesh.hpp"

Mesh::Mesh()
    : vertices(nullptr), indices(nullptr), vertexCount(0), indexCount(0), material(nullptr), position(0, 0), scale(1, 1)
{

}

void Mesh::SetCustomMesh(Vector3 *vertices, Vector2 *uvs, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount, Material *material)
{
    vertexData = new Vertex[vertexCount];
    this->vertices = new Vector3[vertexCount];
    this->uvs = new Vector2[vertexCount];
    this->indices = new unsigned int[indexCount];

    // Copy data to construct vertexData then.
    for(int i = 0; i < vertexCount; i++)
    {
        this->vertices[i] = vertices[i];
        this->uvs[i] = uvs[i];
    }

	for(int i = 0; i < indexCount; i++)
	{
        this->indices[i] = indices[i];
	}

    this->vertexCount = vertexCount;
    this->indexCount = indexCount;
    this->material = material;

    ConstructVertexData();
}

void Mesh::SetPosition(Vector2 position)
{
    if(this->position == position)
        return;
    this->position = position;
    ConstructVertexData();
}

void Mesh::SetScale(Vector2 scale)
{
    if(this->scale == scale)
        return;
    this->scale = scale;
    ConstructVertexData();
}

void Mesh::SetMaterial(Material *material)
{
    if(this->material == material)
        return;
    this->material = material;
    ConstructVertexData();
}

void Mesh::SetQuadMesh(Material *material)
{
    Vector3 pos[] = {
		Vector3(-1, -1, 0),
		Vector3( 1, -1, 0),
		Vector3( 1,  1, 0),
		Vector3(-1,  1, 0)
	};

	Vector2 uv[] = {
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

    unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

    SetCustomMesh(pos, uv, 4, indices, 6, material);
}

void Mesh::ConstructVertexData()
{
	for(int i = 0; i < vertexCount; i++)
	{
        Vector2 pos = (Vector2)vertices[i] * scale + position;
        vertexData[i] = Vertex {
            Vector3(pos.x, pos.y, 0),
            uvs[i],
            material->color
        };
	}
}

Mesh::~Mesh()
{
    if(vertexCount != 0)
    {
        delete [] vertices;
        delete [] uvs;
        delete [] vertexData;
    }
    if(indexCount != 0)
        delete [] indices;
}
