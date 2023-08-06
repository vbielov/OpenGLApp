#pragma once
#include "Texture.hpp"
#include "Vector.hpp"

struct Sprite
{
    Sprite(Texture* atlasTexture, Vector2 uvStart, Vector2 uvEnd);
    Texture* atlasTexture;
    Vector2 uvStart;
    Vector2 uvEnd;
};