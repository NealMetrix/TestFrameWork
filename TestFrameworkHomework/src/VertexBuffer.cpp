#include "VertexBuffer.h"
#include "render.h"

//The constructor will set up our VertexBuffer for us
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //Constructor binds the VertexBuffer automatically when object is instantiated
    GLcall(glGenBuffers(1, &m_rendererID));
    GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLcall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLcall(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::bind()const
{
    GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::unBind()const
{
    GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));//Remember we set what we are binding to 0 to undbind it
}