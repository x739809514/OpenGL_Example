#include "VertexLayout.h"

VertexLayout::VertexLayout():m_stride(0)
{

}

VertexLayout::~VertexLayout()
{
}

std::vector<VertexLayoutElement> VertexLayout::GetLayoutElements()
{
    return m_elements;
}

unsigned int VertexLayout::GetStride()
{
    return m_stride;
}

template<>
void VertexLayout::Push<float>(unsigned int count)
{
    m_elements.push_back({GL_FLOAT,count,GL_FALSE});
    //Todo:is right?
    m_stride+=count * VertexLayoutElement::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexLayout::Push<unsigned char>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE});
    //Todo:is right?
    m_stride+=count * VertexLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

template<>
void VertexLayout::Push<unsigned int>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
    //Todo:is right?
    m_stride+= count * VertexLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
}