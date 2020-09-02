#pragma once
#include "test.h"

namespace tester
{
	class imGuiDemo : public test
	{
	public:
		void onUpdate()override;
		void onRender()override;
		void onImGuiRender()override;
	};
}