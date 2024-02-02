#include "VertexArray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

VertexArray::VertexArray(unsigned int id) : renderId(id)
{
    glGenVertexArrays(1,&renderId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&renderId);
}

void VertexArray::AddLayout(VertexLayout &layout)
{
}

void VertexArray::AddBuffer(VertexBuffer &buffer, VertexLayout &layout)
{
    Bind();
    buffer.Bind();
    const auto lyVec = layout.GetLayoutElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < lyVec.size(); i++)
    {
        std::cout << i << std::endl;
        auto ele = lyVec[i];
        glEnableVertexAttribArray(i);
        auto size = ele.GetSizeOfType(ele.type);
        glVertexAttribPointer(i, ele.count, ele.type, ele.isNormalise, layout.GetStride(), (const void *)offset);
        offset += ele.count * VertexLayoutElement::GetSizeOfType(ele.type);
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
