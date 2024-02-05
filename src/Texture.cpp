#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Texture::Texture(const std::string& path):textureID(0),filePath(path),m_LocalBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
}

Texture::~Texture()
{
}
