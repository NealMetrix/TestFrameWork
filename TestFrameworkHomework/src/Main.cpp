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
#include "tests/testTexture.h"
#include "tests/testsMainMenu.h"
#include "tests/ImGuiTest.h"

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

    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl << std::endl;


    GLcall(glEnable(GL_BLEND));
    GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    renderPipeline renderOb;/*Here we create our render object*/

    ImGui::CreateContext();/*Creating a current context of ImGui*/
    ImGui_ImplGlfwGL3_Init(window, true);/*Feeding data to the window*/
    ImGui::StyleColorsDark();/*Setting the style to dark. Just a style preference*/

    tester::test* currentTestPtr = nullptr;
    tester::mainMenu menu(currentTestPtr);
    currentTestPtr = &menu;
    /*I might want to put menu on the heap just for consistancies sake but then again is there a way to put
    all of them on the stack? No because as far as I know you can't create a stack object.... Well I don't know, if you had the lambda
    return it's own object instance memory address then you might be able create it on the stack. That's probably why cherno used smart pointers
    to keep track of the other classes so he didn't have to delete anything and didn't want to find a way to put them on the stack.*/
        
    /*When you register a lambda you are setting the ptr to a new location*/
    menu.testRegister<tester::testTexture>("Texture Test");
    menu.testRegister<tester::imGuiDemo>("ImGUI Demo");
    menu.testRegister<tester::testClearColor>("Clear Color Test");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderOb.clear();

        /*Still not sure what Cherno's intentions were when having us build this onUpdate*/
        ImGui_ImplGlfwGL3_NewFrame();
        if (currentTestPtr)
        {
            currentTestPtr->onUpdate();
            currentTestPtr->onRender();
            /*I want to only have ImGui::Begin run if the type isn't imGuiDemo*/
            ImGui::Begin("Tests");
            currentTestPtr->onImGuiRender();

            if (currentTestPtr != &menu && ImGui::Button("<-Menu"))
            {
                delete currentTestPtr;
                currentTestPtr = &menu;
            }
            ImGui::End();
        }

        ImGui::CreateContext();
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    if (currentTestPtr != &menu)
        delete currentTestPtr;

    /*Destroying the ImGui context*/
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}