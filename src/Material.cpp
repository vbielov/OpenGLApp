#include "Material.hpp"

Material::Material()
    : shader(nullptr), albedoTexture(nullptr), color()
{
    
}

Material::Material(Shader *shader, Texture *albedoTexture, Vector4 color)
    : shader(shader), albedoTexture(albedoTexture), color(color)
{
}
