#include "render.h"
#include<iostream>
/*GL debug functions*/
void GLclearE()
{
    while (glGetError() != GL_NO_ERROR)
    {

    }
}
bool GLlogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << " : " << line << std::endl;
        return false;
    }
    return true;
}

/*Start of renderPipeline class definitions*/
void renderPipeline::draw(const VertexArray& va, const IndexBuffer& ib, const shaders& shader)const
{
    /*Binding our render components/parameters*/
    shader.bind();
    ib.bind();
    va.bind();

    GLcall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
void renderPipeline::clear()const
{
    GLcall(glClear(GL_COLOR_BUFFER_BIT));/*Here we make it so clearing it is a method of the renderPipeline*/
}