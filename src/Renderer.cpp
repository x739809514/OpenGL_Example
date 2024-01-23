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