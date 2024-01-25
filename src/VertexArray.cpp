#include "VertexArray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray(unsigned int id):renderId(id)
{
}

VertexArray::~VertexArray()
{
}

void VertexArray::AddLayout(VertexLayout &layout)
{
}

void VertexArray::AddBuffer(VertexBuffer &buffer, VertexLayout &layout)
{
    buffer.Bind();
    auto lyVec = layout.GetLayoutElements();
    unsigned int offset;
    for (int i = 0; i < lyVec.size(); i++)
    {
        auto ele = lyVec[i];
        glEnableVertexAttribArray(i);
        auto size = ele.GetSizeOfType(ele.type);
        glVertexAttribPointer(i, ele.count, ele.type, ele.isNormalise, layout.GetStride(),(const void*) offset);
        offset+=ele.count * VertexLayoutElement::GetSizeOfType(ele.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(renderId);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}
