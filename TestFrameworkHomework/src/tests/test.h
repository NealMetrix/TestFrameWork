#pragma once

namespace tester
{
	class test
	{
	public:
		test() {}
		virtual ~test() {}

		virtual void onUpdate(){}
		virtual void onRender(){}
		virtual void onImGuiRender(){}
	};
}