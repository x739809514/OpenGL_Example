#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path):textureID(0),filePath(path),m_LocalBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer=stbi_load(path.c_str(),&m_Width,&m_Height,&m_BPP,4);//m_BPP is number of figure of color
    //generate a texture id
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    //set parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    //submit Image data to GPU
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_LocalBuffer);
}

Texture::~Texture()
{
}
