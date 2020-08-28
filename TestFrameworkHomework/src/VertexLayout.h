#pragma once

#include <vector>
#include "render.h"
#include <GL/glew.h>
/*Hotkey for moving up a whole line up and down in VS is alt+arrowUp*/
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;/*cases only work with ints and chars but remember that GL_FLOAT is just an enum that is unsigned int*/
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_Stride;

public:
	VertexLayout()
		:m_Stride(0){}/*We decide to define the m_Stride as 0 at first.*/

	/*Templates for different types*/
	template <typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> &GetElements()const { return m_elements; }
	inline unsigned int GetStride()const { return m_Stride; }

	~VertexLayout(){}
};