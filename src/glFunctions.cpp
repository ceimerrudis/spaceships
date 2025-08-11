#include "GlobalInclude.h"
#include "glFunctions.h"
#include "Logger.h"
#include "glfw3.h"
#include <glad/glad.h>

void InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        error("Failed to initialize GLAD");
    }

    LOG((char*)glGetString(GL_VERSION));
}

GLFWwindow* CreateWindow(std::string WindowName, int width, int height)
{
    if(!glfwInit())
    {
        error("Failed to initialize glfw");
    }
    
    GLFWwindow* window;
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, WindowName.c_str(), NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        error("Failed to create window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return window;
}