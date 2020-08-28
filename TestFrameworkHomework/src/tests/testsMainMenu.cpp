#include "testsMainMenu.h"
#include "render.h"
#include "imgui-1.6.0/imgui.h"

namespace tester
{
	mainMenu::mainMenu()
		:m_ButtonValue(0)
	{

	}
	mainMenu::~mainMenu()
	{

	}
	void mainMenu::onUpdate(float&)
	{

	}
	void mainMenu::onRender()
	{
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void mainMenu::onImGuiRender()
	{
		if (ImGui::Button("Clear Color Test"))
			m_ButtonValue++;
		ImGui::Text("Button Value: %d", m_ButtonValue);
	}
}