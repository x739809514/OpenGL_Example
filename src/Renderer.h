#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) ClearError();\
        x;\
        ASSERT(CheckError(#x, __FILE__,__LINE__))

static void ClearError();

static bool CheckError(const char* func, const char* file, int line);


class Renderer
{
public:
        Renderer(/* args */);
        ~Renderer();
        void Clear();
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& Shader) const;
};
