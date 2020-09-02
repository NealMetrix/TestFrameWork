#include "testTexture.h"
#include "imgui-1.6.0/imgui.h"

namespace tester
{
	/*After this program runs for a long period of time there is a write access violation in the stb_image.cpp file on line 3970
	To debug this I might need to look at the stb_image documentation more closely possibly even learning more in depth
	how png buffers are formated... Pretty much all warnings have to do with the imGUI files and nothing to do with the
	stb_image or any of the files I have created. There is one warning in the shaders but I have made sure it handles
	the exception of writing to a valid index of the stringstream array*/
	testTexture::testTexture()
		:m_VAO(nullptr),m_IndexBuffer(nullptr),m_Shader(nullptr),m_Texture(nullptr),render(nullptr),m_textureFile("res/texture/NeaLeonardoLogo.png")
	{
		m_VAO = new VertexArray;
		m_VAO->bind();

		float vertexBuffer[] =
		{
			/*Positions - Texture Coordinates*/
			 0.5f, 0.5f,  1.0f, 1.0f,//0
			 0.5f, -0.5f, 1.0f, 0.0f,//1
			-0.5f, -0.5f, 0.0f, 0.0f,//2
			-0.5f, 0.5f, 0.0f, 1.0f//3
		};
		unsigned int indexBuffer[] =
		{
			0,1,3,
			3,2,1
		};
		m_VertexBuffer = new VertexBuffer(vertexBuffer,sizeof(float)*4*4);
		m_VertexBuffer->bind();
		
		VertexLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		m_VAO->addBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = new IndexBuffer(indexBuffer,6);
		m_IndexBuffer->bind();

		m_Shader = new shaders("res/shaderCollection.shader");
		m_Shader->bind();

		/*We still need uniform setup for math, textures, and shaders*/
		/*Texture coordinates and vertex positions should be taken in from the layout*/
		m_Texture = new texture();
		/*I wanted to create a method like this to create a new texture value but I couldn't figure it out*/
		m_Texture->bind();
		m_Shader->setUniform1i("u_texture", 0);

		glm::mat4 proj = glm::ortho(-2.0f,2.0f,-1.125f,1.125f);//16:9 aspect ratio

		m_Shader->setUniformMat4f("uniformMVP", proj);

		render = new renderPipeline;
	}
	testTexture::~testTexture()
	{
		delete m_VertexBuffer;
		delete m_IndexBuffer;
		delete m_Shader;
		delete render;
		delete m_VAO;
		delete m_Texture;
	}
	void testTexture::onUpdate()
	{

	}
	void testTexture::onRender()
	{
		GLcall(glClearColor(0.0f,0.0f,0.0f,1.0f));/*Setting up the default background color*/
		GLcall(glClear(GL_COLOR_BUFFER_BIT));

		m_Texture->setTexture(m_textureFile.c_str());
		render->draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}
	void testTexture::onImGuiRender()
	{
		const char* fileList[] = { "res/texture/NeaLeonardoLogo.png","res/texture/chernoLogo.png","res/texture/primeColorBlueCutOut.png","res/texture/Tear.png" };
		/*I need to create a glm pull down menu that will change the value of current */
		const char* items[] = { "NeaLeonardo Logo", "Cherno Logo", "Blue Magic Orb", "Tear" };/*I should find a way to automate how the fileList relates to the items name*/
		/*I have noticed that the program slows down when the Blue Magic Orb is selected. I think this is just because it corresponds to such a
		large png file when it needs to be loaded which slows down how quickly it can get to the next cycle of onImGui since that happens
		after onRender in the main cpp*/
		static const char* item_current = items[0];
		if (ImGui::BeginCombo("Texture", item_current)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (item_current == items[n]);
				if (ImGui::Selectable(items[n], is_selected))
					item_current = items[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

				/*Setting the texture file to whatever the filelist is selected*/
				if (item_current == items[n])
				{
					m_textureFile = fileList[n];
				}
			}
			ImGui::EndCombo();
		}
	}
}