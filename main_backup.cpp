#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "fps_camera.h"
#include <iostream>

const unsigned int width = 800;
const unsigned int height = 600;
const float pi = 3.14;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = width / 2;
float lastY = height / 2;
bool  firstMouse = true;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, "FPS", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        return -1;
    }

    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_DEPTH_TEST);

    ResourceManager::LoadShader("shaders/2d.vert", "shaders/common.frag", nullptr, "2d");
    ResourceManager::LoadShader("shaders/3d.vert", "shaders/common.frag", nullptr, "3d");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("2d").Use().SetInteger("2d", 0);
    ResourceManager::GetShader("2d").SetMatrix4("projection", projection);
    ResourceManager::GetShader("3d").Use().SetInteger("3d", 0);
    ResourceManager::LoadTexture("textures/clover.jpg", GL_FALSE, "ground");
    ResourceManager::LoadTexture("textures/crosshair.png", GL_FALSE, "crosshair");
    Shader shader2d = ResourceManager::GetShader("2d");
    Shader shader3d = ResourceManager::GetShader("3d");
    SpriteRenderer* Renderer2d = new SpriteRenderer(shader2d);
    SpriteRenderer* Renderer3d = new SpriteRenderer(shader3d);
    Texture2D ground = ResourceManager::GetTexture("ground");
    Texture2D crosshair = ResourceManager::GetTexture("crosshair");

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glm::mat4 view = camera.GetViewMatrix();
        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width/height, 0.1f, 100.0f);
        // Renderer3d->DrawSprite(ground, glm::vec3(0, 0, 30.0f), glm::vec2(width, height), pi/6, glm::vec3(1.0f, 0.0f, 0.0f), view, projection);
        Renderer2d->DrawSprite(crosshair, glm::vec2(width/2-40, height/2-40), glm::vec2(80, 80));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    (void)window;
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    (void)window;
    (void)xoffset;
    camera.ProcessMouseScroll(yoffset);
}
