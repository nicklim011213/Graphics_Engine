// Graphics_Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad.h> 
#include <glfw3.h>
#include <iostream>
#include <unordered_map>
#include "boost/filesystem.hpp"

#include "ShaderHandler.h"
#include "RenderPipeline.h"
#include "Camera.h"
#include "PipelineFunctions.h"
#include "SceneFunctions.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera* camera, Utilites* util);

int main()
{
    boost::filesystem::path _ = boost::filesystem::initial_path();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL);
    if (window == NULL)
        return -1;

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -2;

    glViewport(0, 0, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Shader Block
    Shader Shader1("prespective_color.vs");
    Shader Shader2("ColorInVertex.fs");

    ShaderProgram ShaderProgram1;
    ShaderProgram1.AttachShader(Shader1);
    ShaderProgram1.AttachShader(Shader2);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f);
    Camera camera;

    ShaderProgram1.UseShaders();
    glUseProgram(ShaderProgram1.GetShaderProgramID());
    ShaderProgram1.SetShaderValue("model", model);
    ShaderProgram1.SetShaderValue("projection", proj);
    ShaderProgram1.SetShaderValue("view", camera.view);
	// Shader Block End

    Utilites util;

    Model Model1("BoxStd2.obx");

    Scene Scene1;
	Scene1.AttachModelHandler(AddModelVertexColor);
	Scene1.AttachModel(Model1);

    RenderPipeline MyPipeline;
	MyPipeline.AttachImplementation(VertexColor);
	std::vector<RenderBufferObjects> RBOs = MyPipeline.Execute(Scene1);


    while (!glfwWindowShouldClose(window))
    {
        util.RefreshDeltaTime();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window, &camera, &util);
        camera.HandleMouse(window);

        glUseProgram(ShaderProgram1.GetShaderProgramID());
        ShaderProgram1.SetShaderValue("view", camera.view);
		for (RenderBufferObjects RBO : RBOs)
		{
            glBindVertexArray(RBO.VAO);
            glDrawElements(GL_TRIANGLES, Scene1.GetIndexs().size(), GL_UNSIGNED_INT, 0);
		}
        glfwSwapBuffers(window);
        glfwPollEvents();   
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera* camera, Utilites* util)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->forward(util);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->backwards(util);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->left(util);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->right(util);
}
