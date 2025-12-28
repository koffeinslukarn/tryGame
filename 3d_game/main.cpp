#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "world.h"

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Game", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    World world;

    bool gameRunning = true; // gö inte denna till const

    while (gameRunning && !glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        world.update(0.016f); // upddatera endligt standardvärde
        world.draw();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
