#pragma once
#include "GameObject.hpp"
#include <vector>
#include <algorithm>

class Scene
{
public:
    static Scene* currentScene;
    static Scene* menuLevel;
    static Scene* mainLevel;

    Scene();
    ~Scene();

    static void Load(Scene* scene);

    void UpdateGameLoop();
    void Instantiate(GameObject* gameObject);
    void Destroy(GameObject* gameObject);
private:
    std::vector<GameObject*> gameObjects;
};