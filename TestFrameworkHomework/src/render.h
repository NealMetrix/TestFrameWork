#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

/*OpenGL debugging definitions and functions*/
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLcall(x) GLclearE();\
    x;\
    ASSERT(GLlogCall(#x, __FILE__, __LINE__))

void GLclearE();
bool GLlogCall(const char* function, const char* file, int line);

/*renderer class*/
class renderPipeline
{
private:
    /*I am uncertain why we didn't just create a struct since there are no private variables*/
public:
    void draw(const VertexArray& va, const IndexBuffer& ib, const shaders& shader)const;
    void clear()const;
};