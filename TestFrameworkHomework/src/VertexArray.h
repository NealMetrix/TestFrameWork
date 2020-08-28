#pragma once

#include "VertexBuffer.h"

class VertexLayout;

class VertexArray
{
private:
	unsigned int m_rendererID;

public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb,const VertexLayout& layout);

	void bind()const;
	void unbind()const;
};