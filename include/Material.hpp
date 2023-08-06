#pragma once
#include "Vector.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class Material
{
public:
    Shader* shader;
    Texture* albedoTexture;
    Vector4 color;
    Material();
    Material(Shader* shader, Texture* albedoTexture, Vector4 color);
private:

};