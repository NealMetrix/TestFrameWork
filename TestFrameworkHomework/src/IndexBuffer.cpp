#include "IndexBuffer.h"
#include "render.h"

/*IndexBufferer Bound in constructor*/
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));//Won't allow us to run the program if unsigned int is not the same size as GLuint datatype

    GLcall(glGenBuffers(1, &m_rendererID));
    GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
    GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLcall(glDeleteBuffers(1, &m_rendererID));
}

//By calling this function we can rebind the buffer
void IndexBuffer::bind()const
{
    GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

//By call this function we can unBind a selected Buffer
void IndexBuffer::unBind()const
{
    GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));//Remember we set what we are binding to 0 to undbind it
}