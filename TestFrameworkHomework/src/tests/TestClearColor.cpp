#include "TestClearColor.h"
#include "render.h"
#include "imgui-1.6.0/imgui.h"
namespace tester
{
	testClearColor::testClearColor()
		:m_clearColor{0.2f,0.5f,1.0,1.0}
	{

	}
	testClearColor::~testClearColor()
	{

	}
	void testClearColor::onUpdate(float& deltaTime)
	{

	}
	void testClearColor::onRender()
	{
		GLcall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));/*Setting up the default background color*/
		GLcall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void testClearColor::onImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_clearColor);/*We set it up so there is a color picker that displays the 
													   default background with imGui so we can interact with it.*/
	}
}