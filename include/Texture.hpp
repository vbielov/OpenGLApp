#pragma once
#include "Window.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Texture
{
public:
    Texture(const char* pngPath);
    Texture(unsigned char* bufferSource, int width, int height);
    ~Texture();
    void Bind(unsigned int slot) const;
    void Unbind() const;

    static Texture* menuButton;
    static Texture* player;
private:
    unsigned int id;
    int width;
    int height;
    void CreateTexture(unsigned char* bufferSource, int width, int height);
    void WriteImageHeaderFile(unsigned char* bufferSource);
};