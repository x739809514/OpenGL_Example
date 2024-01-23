#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) ClearError();\
        x;\
        ASSERT(CheckError(#x, __FILE__,__LINE__))

void ClearError();

bool CheckError(const char* func, const char* file, int line);