#include "testsMainMenu.h"
#include "render.h"
#include "imgui-1.6.0/imgui.h"

namespace tester
{
	mainMenu::mainMenu(test*& testPtr)
		:m_currentTest(testPtr)
	{
		/*What needs to happen*/
	}
	void mainMenu::onImGuiRender()
	{
		/*When do I want to create all the buttons in the vector*/
		for (unsigned int i = 0; i<m_tests.size(); i++)
		{
			if (ImGui::Button(m_tests.at(i).name))
			{
				m_currentTest = m_tests.at(i).testGenerator();
			}
		}
		//ImGui::Text("Button Value: %d", m_ButtonValue);
	}
}