#include "texture.h"
#include "stb/stb_image.h"

texture::texture()
	:m_rendererID(0),m_filePath("res/texture/NeaLeonardoLogo.png"),m_localBuffer(nullptr),m_width(0),m_height(0),m_BPP(0)
{
	/*Moved loading the pixel buffer into the new setTexture method*/

	GLcall(glGenTextures(1, &m_rendererID));
	GLcall(glBindTexture(GL_TEXTURE_2D,m_rendererID));

	/*4 texture parameters (at minimum these 4 parameters must be specified to render a texture)*/
	GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR));
	GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	setTexture(m_filePath);

	GLcall(glBindTexture(GL_TEXTURE_2D, 0));/*texture not bound by default*/

	if (m_localBuffer)/*Basically saying that if the buffer does contain data free our localBuffer member*/
		stbi_image_free(m_localBuffer);
}
texture::~texture()
{
	GLcall(glDeleteTextures(1, &m_rendererID));
}

void texture::bind(unsigned int slot)const
{
	GLcall(glActiveTexture(GL_TEXTURE0 + slot));/*specifying the slot the texture occupies*/
	GLcall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}
void texture::unbind()const
{
	GLcall(glBindTexture(GL_TEXTURE_2D, 0));
}
void texture::setTexture(std::string file_path)/*This is how we now set the pixel buffer*/
{
	m_filePath = file_path;
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_BPP, 4);
	GLcall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
}