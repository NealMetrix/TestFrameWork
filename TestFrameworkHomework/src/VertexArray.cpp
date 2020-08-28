#include "VertexArray.h"
#include "VertexLayout.h"
#include "render.h"
#include <GL/glew.h>

VertexArray::VertexArray()
{
	GLcall(glGenVertexArrays(1, &m_rendererID));
	GLcall(glBindVertexArray(m_rendererID));
}

VertexArray::~VertexArray()
{
	GLcall(glDeleteVertexArrays(1, &m_rendererID));/*We need to make sure we delete memory from the GPU*/
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)/*.size is a method of vector*/
	{
		const auto& element = elements[i];
		GLcall(glEnableVertexAttribArray(i));
		GLcall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*) offset));
		offset+=element.count*VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind()const
{
	GLcall(glBindVertexArray(m_rendererID));
}
void VertexArray::unbind()const
{
	GLcall(glBindVertexArray(0));
}