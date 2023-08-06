#include "Scene.hpp"

Scene* Scene::currentScene = nullptr;
Scene* Scene::menuLevel = nullptr;
Scene* Scene::mainLevel = nullptr;

Scene::Scene()
    : gameObjects()
{
    
}

Scene::~Scene()
{

}

void Scene::Instantiate(GameObject* gameObject)
{
    gameObjects.push_back(gameObject);
}

void Scene::Destroy(GameObject* gameObject)
{
    auto index = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
    gameObjects.erase(index);
}

void Scene::Load(Scene* scene)
{
    currentScene = scene;
}

void Scene::UpdateGameLoop()
{
    int amountOfGameObjects = gameObjects.size();
    for(int i = 0; i < amountOfGameObjects; i++)
    {
        gameObjects[i]->Update();
        gameObjects[i]->Draw();
    }
}
