#pragma once
#include "test.h"

namespace tester
{
	class testClearColor : public test
	{
	public:
		testClearColor();
		~testClearColor();/*We're not going to mark this as virtual because the base class/parent class is.*/
		void onUpdate() override;
		void onRender()override;
		void onImGuiRender()override;
	private:
		float m_clearColor[4];
	};
}