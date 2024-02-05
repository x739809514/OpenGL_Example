#pragma once

class IndexBuffer
{
private:
    unsigned int bufferId;
public:
    IndexBuffer(unsigned int size, const void *data);
    virtual ~IndexBuffer();
    void Bind() const;
    void UnBind() const;
};
