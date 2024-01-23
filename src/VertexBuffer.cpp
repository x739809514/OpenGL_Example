#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(unsigned int size, const void *data)
{
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &bufferId);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void VertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
