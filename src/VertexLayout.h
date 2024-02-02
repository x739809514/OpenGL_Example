#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertexLayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned char isNormalise;

    static unsigned int GetSizeOfType(unsigned int  type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4; 
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class VertexLayout
{
private:
    std::vector<VertexLayoutElement> m_elements;
    unsigned int m_stride;
public:
    VertexLayout(/* args */);
    ~VertexLayout();

    template <typename T>
    void Push(unsigned int type)
    {
    }

    std::vector<VertexLayoutElement> GetLayoutElements();
    unsigned int GetStride();
};


