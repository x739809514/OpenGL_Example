#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{

    if (glfwInit() == false)
    {
        return -1;
    }
    // set opengl version, here is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // set opengl config file
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // make opengl forward compat, that means forbid some functions in opengl 2.x which area abandoned
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "MyFirstOpenGLWin", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "fail to create a window" << std::endl;
        // release assets when window quits
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // make cur thread context is the opengl context
    glfwMakeContextCurrent(window);
    // glad is a library which is used to manage function pointer of opengl
    // since opengl is cross-platform, it doesn't bind function to any specific platform
    // so we need to get pointers form opengl and manage them
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
    {
        std::cout << "fail to load glad" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    float positions[] = {
        -0.5f,-0.5f,0.0f,0.0f,
        0.5f,-0.5f,1.0f,0.0f,
        0.5f,0.5f,1.0f,1.0f,
        -0.5f,0.5f,0.0f,1.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO);

    VertexBuffer vb(4 * 4 * sizeof(float), positions);

    VertexLayout vl;
    vl.Push<float>(2);
    vl.Push<float>(2);
    VertexArray va(VAO);
    va.Bind();
    va.AddBuffer(vb,vl);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    //unsigned int ibo;
    IndexBuffer indexBuffer(6 * sizeof(unsigned int), indices);
    //glBindVertexArray(0);
    va.UnBind();

    glm::mat4 proj = glm::ortho(-2.0f,2.0f,-1.5f,1.5f,-1.0f,1.0f);

    // ShaderProgram source = ParseShader("/Users/innovation/CodePlace/OpenGL_Example/src/resource/shader/Triangle.shader");
    // std::cout << "Vertex" << std::endl;
    // std::cout << source.vertex << std::endl;
    // std::cout << "Fragment" << std::endl;
    // std::cout << source.fragment << std::endl;
    // unsigned int shader = CreateShader(source.vertex, source.fragment);
    Shader shader("/Users/innovation/CodePlace/OpenGL_Example/src/resource/shader/Triangle.shader");
    int location = shader.GetLocationOfUniform("u_color");

    // int location = glGetUniformLocation(shader, "u_color");
    float r = 0.0f;
    float increment = 0.0f;
    shader.Bind();
    shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);
    shader.SetUniformMat4f("u_MVP",proj);
    // glUseProgram(0);

    // start rendering
    Renderer renderer;
    Texture texture("/Users/innovation/CodePlace/OpenGL_Example/src/resource/texture/darksoul.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture",0);
    while (glfwWindowShouldClose(window) == false)
    {
        // detect key escape event
        processInput(window);
        // set clear color
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        renderer.Clear();
        // clear color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        shader.SetUniform4f("u_Color",r, 0.8f, 0.5f, 1.0f);
        // if (location != -1)
        // {
        //     glUniform4f(location, r, 0.8f, 0.5f, 1.0f);
        // }

        


        if (r >= 1.0f)
        {
            increment -= 0.2f;
        }
        else if (r <= 0.0f)
        {
            increment += 0.2f;
        }
        r += increment;

        //glBindVertexArray(VAO);
        // va.Bind();
        // glUseProgram(shader);
        // shader.Bind();
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // indexBuffer.Bind();
        // glDrawArrays(GL_TRIANGLES,0,6);
        renderer.Draw(va,indexBuffer,shader);
        // double buffer tech
        glfwSwapBuffers(window);
        // func call all the event since the last call
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
