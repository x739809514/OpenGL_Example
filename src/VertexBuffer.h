#pragma once

class VertexBuffer
{
private:
    unsigned int bufferId;

public:
    VertexBuffer(unsigned int size, const void *data);
    virtual ~VertexBuffer();
    void Bind();
    void UnBind();
};