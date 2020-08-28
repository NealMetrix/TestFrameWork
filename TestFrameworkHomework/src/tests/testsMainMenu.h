#pragma once
#include "test.h"

namespace tester
{
	class mainMenu : public test
	{
	public:
		mainMenu();
		~mainMenu();
		void onUpdate(float&)override;
		void onRender()override;
		void onImGuiRender()override;
	private:
		unsigned int m_ButtonValue;
	};
	/*I need buttons in this and when you click on a button the current main menu instance will stop
	existing and then another subtype of test will be triggered like our testClearColor subtype of the test class.
	Whenever we press a button the button value should change. Let's remember though that Cherno also made the 
	destructor of the parent class virual... Why??? Does that mean we can override when the class gets destroyed????*/
}