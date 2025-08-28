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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* CreateWindow(std::string WindowName, int width, int height)
{
    if(!glfwInit())
    {
        error("Failed to initialize glfw");
    }
    
    GLFWwindow* window;
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    width = mode->width-100;
    height = mode->height-100;                                    //monitor
    window = glfwCreateWindow(width, height, WindowName.c_str(), NULL, NULL);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!window)
    {
        glfwTerminate();
        error("Failed to create window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return window;
}