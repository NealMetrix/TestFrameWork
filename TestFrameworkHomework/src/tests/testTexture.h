#pragma once
#include "test.h"

#include "render.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "texture.h"
#include "glm/glm.hpp"

#include <memory>
#include <iostream>
namespace tester
{
	struct imageSelect
	{
		std::string img_Name;
		std::string filePath;
	};
	class testTexture : public test
	{
	public:
		testTexture();
		~testTexture();/*We're not going to mark this as virtual because the base class/parent class is.*/
		void onUpdate() override;
		void onRender()override;
		void onImGuiRender()override;
	private:
		/*Remember that you'll need to delete these if we don't make them unique pointers*/
		VertexArray* m_VAO;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		shaders* m_Shader;/*This test we'll do with the shader we can try and make different shaders available by switching what the shaderFilepath is*/
		texture* m_Texture;
		renderPipeline* render;

		std::string m_textureFile;
	};
}