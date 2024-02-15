#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

Texture::Texture(const std::string &path) : textureID(0), filePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);                                     // flip our texture, make it up side down
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4); // m_BPP 是每个像素的位数
    // generate a texture id
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // set parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // submit Image data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    // clear it after all
    glBindTexture(GL_TEXTURE_2D, 0);
    if (m_LocalBuffer)
    {
        stbi_image_free(m_LocalBuffer);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::UnBind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
