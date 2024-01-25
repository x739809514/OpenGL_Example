#include "VertexLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
private:
    unsigned int renderId;
public:
    VertexArray(unsigned int renderID);
    ~VertexArray();
    void AddLayout(VertexLayout& layout);
    void AddBuffer(VertexBuffer& buffer,VertexLayout& layout);
    void Bind() const;
    void UnBind() const;
};

