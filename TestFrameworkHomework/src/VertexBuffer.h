#pragma once

class VertexBuffer
{
private:
	unsigned int m_rendererID;//This is a variable we make to keep track of all the different VertexBuffer Objects we make in OpenGL

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	
	void bind()const;
	void unBind()const;
};