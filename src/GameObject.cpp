#include "GameObject.hpp"

int GameObject::gameObjectsCounter = 0;

GameObject::GameObject()
    : id(GameObject::gameObjectsCounter++)
{

}

GameObject::~GameObject()
{
    
}