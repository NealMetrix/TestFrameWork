#pragma once
/*This is going to start as the base class for all the test stuff.
We put it in a namespace so it's seperated from all the libraries and
OpenGL stuff we have got going on already.*/

namespace tester
{
	class test
	{
	public:
		test() {}
		virtual ~test() {}

		virtual void onUpdate(float&){}
		virtual void onRender(){}

		/*This is where we are drawing our imGui stuff*/
		virtual void onImGuiRender(){}
		/*Our goal is to make these functions as simple as possible so when we make subclasses for these functions
		we can easily override them and create polymorphic windows. Like for the onImGuiRender function we can
		replace it with any of the ImGui that's relevant to the window. The actual setUp code will be in the
		constructor and destructor so any stack variables that are tied to the lifetime of our class, like a vertex
		buffer, could be a stack variable in our class scope which means we don't need to worry about manual memory 
		management at all. Because the vertex buffer will be destroyed when the class is destroyed.*/
	};
}