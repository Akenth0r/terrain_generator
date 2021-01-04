#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <gtc/noise.hpp>
#include "PerlinNoise.h"

using namespace std;

// Function declarations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


// Constants
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 600;
const char* WINDOW_TITLE = "Terrain generator";

// Variables
GLFWwindow* window;


int main()
{
    if (!glfwInit())
    {
        cout << "Error! Glfw was not initialized." << endl;
    }
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetKeyCallback(window, key_callback);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    printf("GLEW: %s\n", glewGetString(GLEW_VERSION));

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        
        // Doing some stuff
        //glfwDestroyWindow(window);
        //glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    /*glfwDestroyWindow(window);
    glfwTerminate();*/
    exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
