#pragma once
#include "test.h"
#include<vector>
#include<functional>
#include<iostream>

namespace tester
{
	struct testArea
	{
		const char* name;
		std::function<test*()> testGenerator;
	};
	class mainMenu : public test
	{
	public:
		mainMenu(test*& testPtr);
		void onImGuiRender()override;

		template<typename T>
		void testRegister(const char* name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_tests.push_back({ name,[]() { return new T; } });
			/*We did this the button can render the name and then call this lambda later*/
		}
	private:
		std::vector<testArea> m_tests;
		test*& m_currentTest;
	};
	/*I need buttons in this and when you click on a button the current main menu instance will stop
	existing and then another subtype of test will be triggered like our testClearColor subtype of the test class.
	Whenever we press a button the button value should change. Let's remember though that Cherno also made the 
	destructor of the parent class virual... Why??? Does that mean we can override when the class gets destroyed????*/
}