#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

#include "render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"
#include "Shader.h"
#include "texture.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui-1.6.0/imgui.h"
#include "imgui-1.6.0/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/testsMainMenu.h"

/*This is where I do Cherno's homework and work on making a menu that takes us to all of our tests.*/

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /*OpenGL version and mode switch*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Blue Square", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    glewInit();

    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl << std::endl;//This prints the version of OpenGL we are using

    {//Start of scope to destroy stack allocated Buffers
        GLcall(glEnable(GL_BLEND));/*Be sure to enable blending*/
        GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        renderPipeline renderOb;/*Here we create our render object*/

        ImGui::CreateContext();/*Creating a current context of ImGui*/
        ImGui_ImplGlfwGL3_Init(window, true);/*Feeding data to the window*/
        ImGui::StyleColorsDark();/*Setting the style to dark. Just a style preference*/

        unsigned int windowValue = 1;
        tester::mainMenu menu;/*If I put an if statement around this it will end the scope too early*/
        
        /*Can I create a lambda that make different object instances*/

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderOb.clear();

            menu.onRender();

            ImGui_ImplGlfwGL3_NewFrame();

            ImGui::CreateContext();
            menu.onImGuiRender();

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        
    }//scope of buffers ends right before GLFW Terminate
    /*Destroying the ImGui context*/
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}