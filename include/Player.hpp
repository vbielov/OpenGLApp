#pragma once
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "LineRenderer.hpp"

class Player : public GameObject
{
public:
    Player(Vector3 position, Vector2 scale, Sprite sprite);
    ~Player();
    void Update();
    void Draw();
private:
    Vector2 position;
    Material material;
    Mesh mesh;
};