#include <iostream>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>




void fps_titel (GLFWwindow *window, std::chrono::high_resolution_clock::time_point &lastTime, int &frames);
void processInput (GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height); 

int main (int argc, char *argv[])
{
  std::cout << "hello cmake!!!" << std::endl;
  // init window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // call back
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);
  
  // init GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // varibols
  auto lastTime = std::chrono::high_resolution_clock::now();
  int frames = 0;

  // main loop
  while(!glfwWindowShouldClose(window))
  {
    frames ++;

    processInput(window);

    fps_titel(window, lastTime, frames);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glfwSwapBuffers(window);
    glfwPollEvents();    
  }


  glfwTerminate();
  return 0;
}

void processInput (GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void fps_titel(GLFWwindow *window, 
               std::chrono::high_resolution_clock::time_point& lastTime, 
               int& frames)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

    if (elapsed >= 1000) {
        double fps = frames * 1000.0 / elapsed;

        std::string title = "FPS: " + std::to_string((int)fps);
        glfwSetWindowTitle(window, title.c_str());

        frames = 0;
        lastTime = currentTime;
    }
}
