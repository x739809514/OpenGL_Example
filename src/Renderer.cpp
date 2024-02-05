#include "Renderer.h"
#include <iostream>

#pragma region Error
static void ClearError()
{
    while (glGetError()!=GL_NO_ERROR);
}

static bool CheckError(const char* func, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error:]" << error << file << ": " << line << std::endl;
        return false;
    }
    return true;
    
}
#pragma endregion

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
