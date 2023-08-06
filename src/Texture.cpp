#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture* Texture::menuButton = nullptr;
Texture* Texture::player = nullptr;

Texture::Texture(const char *pngPath)
    : id(0), width(0), height(0)
{
    // opengl starts at bottom left
	// png format starts at upper left
	// so have to flip texture:
	stbi_set_flip_vertically_on_load(1);
    int BPP;
	unsigned char* localBuffer = stbi_load(pngPath, &width, &height, &BPP, 4); // RGBA - 4 values

    CreateTexture(localBuffer, width, height);
    // WriteImageHeaderFile(localBuffer);

    if(localBuffer)
		stbi_image_free(localBuffer);
}

Texture::Texture(unsigned char* bufferSource, int width, int height)
    : id(0), width(width), height(height)
{
    CreateTexture(bufferSource, width, height);
}

void Texture::CreateTexture(unsigned char* bufferSource, int width, int height)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferSource);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::WriteImageHeaderFile(unsigned char *bufferSource)
{
    std::ostringstream oss;
    oss << "unsigned char icon_png[] = {";

    for (int i = 0; i < width * height * 4; ++i) {
        if (i % 16 == 0)
            oss << "\n  ";
        oss << "0x" << std::hex << static_cast<int>(bufferSource[i]);
        if (i < width * height * 4 - 1)
            oss << ", ";
    }

    oss << "\n};\n";
    oss << "const int icon_width = " << width << ";\n";
    oss << "const int icon_height = " << height << ";\n";

    std::string headerData = oss.str();

    // Save the header data to a file
    std::ofstream outFile("icon_data.h");
    outFile << headerData;
    outFile.close();
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}