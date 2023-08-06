#pragma once
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include <functional>

class Button : public GameObject
{
public:
    Button(Vector3 position, Vector2 scale, Sprite sprite, void (*func)());
    ~Button();
    void Update();
    void Draw();
private:
    Material material;
    Mesh mesh;
    void (*callback)();
    
    bool MousePositionInCollider();
};