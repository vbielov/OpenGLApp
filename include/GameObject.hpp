#pragma once

class GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void Update() = 0;
    virtual void Draw() = 0;
private:
    int id;
    static int gameObjectsCounter;
};