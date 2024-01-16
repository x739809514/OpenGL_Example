#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define ASSERT(x) if(!(x)) break;
#define GLCALL(x) ClearError();\
        x;\
        ASSERT(CheckError(#x, __FILE__,__LINE__))

enum class ShaderType
{
    None = -1,
    Vertex =0,
    Fragment = 1,
};

struct ShaderProgram
{
    std::string vertex;
    std::string fragment;
};

#pragma region Error
static void ClearError()
{
    while (glGetError()!=GL_NO_ERROR);
}

static bool CheckError(const char* func, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error:]" << error << file << ": " << line << std::endl;
        return false;
    }
    return true;
    
}
#pragma endregion

static ShaderProgram ParseShader(const std::string filepath)
{
    std::ifstream inFile(filepath);
    std::string line;
    ShaderType type = ShaderType::None;
    std::stringstream ss[2];

    while (getline(inFile,line))
    {
        if(line.find("#Shader")!=std::string::npos)
        {
            if(line.find("vertex")!=std::string::npos)
            {
                // get vertex str
                type = ShaderType::Vertex;
            }else if(line.find("fragment")!=std::string::npos)
            {
                // get fragment str
                type = ShaderType::Fragment;
            }
        }else{
            ss[(int)type] << line << '\n';
        }
    }
    inFile.close();
    return {ss[0].str(),ss[1].str()};
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static unsigned int CompileShader(unsigned int type, std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *str = source.c_str();
    glShaderSource(id, 1, &str, NULL);
    glCompileShader(id);

    //Error handing
    int success;
    glGetShaderiv(id,GL_COMPILE_STATUS,&success);
    if(success == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* info = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id,length,&length,info);
        std::cout<< "Error: "<< (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << "Shader Compiled Failed!"<< info << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(std::string &vertextShader, std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertextShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
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
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
        // 0.5f, 0.5f,
        // -0.5f, 0.5f,
        // -0.5f, -0.5f,
        };
    unsigned int indices[]={
        0,1,2,
        2,3,0
    };
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int ido;
    glGenBuffers(1, &ido);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ido);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);

    ShaderProgram source = ParseShader("/Users/innovation/CodePlace/OpenGL_Example/src/resource/shader/Triangle.shader");
    std::cout << "Vertex" << std::endl;
    std::cout << source.vertex << std::endl;
    std::cout << "Fragment" << std::endl;
    std::cout << source.fragment << std::endl;
    unsigned int shader = CreateShader(source.vertex,source.fragment);
    


    // start rendering
    while (glfwWindowShouldClose(window) == false)
    {
        // detect key escape event
        processInput(window);
        // set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // clear color buffer
        glClear(GL_COLOR_BUFFER_BIT);

#pragma region already abandoned
        // draw triangle
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(0, 0.5f);
        // glVertex2f(0.5f, -0.5f);
        // glEnd();
#pragma endregion
        glBindVertexArray(VAO);
        glUseProgram(shader);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
        //glDrawArrays(GL_TRIANGLES,0,6);

        // double buffer tech
        glfwSwapBuffers(window);
        // func call all the event since the last call
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
