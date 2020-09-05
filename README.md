# TestFrameWork
I am building a quick framework to test different aspects of OpenGL where each class is a different test.

This was originally part of a challenge from Cherno's OpenGL series before I entered school. But I really didn't understand how to solve the problem and had to move to the next tutorial to find out the solution. Now I am backtracking and going to try and try to solve the issues that Cherno solved in my own way and try and also just create more tests for the framework to use so I can better understand how OpenGL and C++ work to solidify a couple of concepts in my mind such as smart pointers, different methods for rendering multiple objects, maybe some other tests. It will also be a good tool to create to try and quickly create frameworks to understand OpenGL better without starting a whole new project to test out the concept quickly and easily.

# Current State
I have added a test that contains the demo of ImGui... This will be extremely usefule for trying to implement different ImGui features in the future because I will be able to look into what features ImGui has and from their I can just look at the source code for the ImGui demo and then implement it the way I would like it to be used.

I was actually able to use the ImGui demo to help me build a texture test. This was a simple ImGui UI that allowed you to display whatever texture is displayed on a square. As of now there are only 4 images.
__Texture Test Images__
- A Dragon Logo
- Cherno's (A YouTuber Of C++ Tutorials) Logo
- Magic Blue Orb
- Tear Drop

# Known Issues
__Test Texture Broken__
As soon as you enter the Texture Test it will appear as expected at first but if you wait for any extended period of time the textures will become discolored and sometimes flicker constantly. Go back into a different menu doesn't seem to fix the issue and it will always end up with an assert being called in the stb cpp files. 

__Lag On Magic Blue Orb__
The Texture test will lag whenever the magic blue orb image is selected. But this might be because it is such a large file size compared to the other files. I also might be constantly loading in the file which would make it even slower. Optimizing this is probably necessary.
