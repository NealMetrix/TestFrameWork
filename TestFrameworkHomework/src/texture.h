#pragma once
#include "render.h"

class texture
{
private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_BPP;/*Stores data of each pixel such as width height and bits per pixel of the texture*/

public:
	texture(const std::string& path);
	~texture();

	void bind( unsigned int slot = 0)const;
	void unbind()const;

	inline int getwidth()const { return m_width; }
	inline int getheight()const { return m_height; }
};