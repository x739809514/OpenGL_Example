#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// } 

// void processInput(GLFWwindow *window)
// {
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

const int screen_width = 800;
const int screen_hight = 600;
 
//三角形的顶点数据
const float triangle[] = {
    //--位置--//
    -0.5f,-0.5f,0.0f,//左下
    0.5f,-0.5f,0.0f,//右下
    0.0f,0.5f,0.0f,//正上
};

int main()
{
    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MAC OSX needs

    // GLFWwindow* window = glfwCreateWindow(800, 600, "HelloOpenGL", NULL, NULL);
    // if (window == NULL)
    // {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }
    // glfwMakeContextCurrent(window);

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }   

    // glViewport(0, 0, 800, 600);
    // while(!glfwWindowShouldClose(window))
    // {
    //     processInput(window);

    //     glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();    
    // }
    // glfwTerminate();
    
    // return 0;

    //初始化GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MAC OSX needs
 
    //创建窗口(宽、高、窗口名)
    auto window = glfwCreateWindow(screen_width, screen_hight, "Triangle", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to Create OpenGL Context" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
 
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
 
    //创建视口
    glViewport(0, 0, screen_width, screen_hight);
 
    //生成并绑定VBO
    GLuint vertex_buffer_object;
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    //将顶点数据绑定至默认的缓冲中
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    //生成并绑定VAO
    GLuint vertex_array_object;
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
 
    //设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//参数：顶点着色器位置值，分量，顶点数据类型，是否标准化，步长、数据偏移量
    glEnableVertexAttribArray(0);//开启0通道
 
    //设置完成之后就可以解绑VBO、VAO了
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    //顶点着色器源码
    const char* vertex_shader_source =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos,1.0);\n"
        "}\n\0";
 
    //片段着色器源码
    const char* fragment_shader_source =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f,0.1f,0.1f,1.0f);\n"
        "}\n\0";
 
    //生成并编译着色器
    //顶点着色器
    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    int success;
    char info_log[512];
    // 检查着色器是否成功编译，如果编译失败，打印错误信息
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }
    // 片段着色器
    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    // 检查着色器是否成功编译，如果编译失败，打印错误信息
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }
    // 链接顶点和片段着色器至一个着色器程序
    int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    // 检查着色器是否成功链接，如果链接失败，打印错误信息
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }
    // 删除着色器
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
 
    // 线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 
    //渲染循环
    while (!glfwWindowShouldClose(window)) {
 
        // 清空颜色缓冲
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        // 使用着色器程序
        glUseProgram(shader_program);
 
        // 绘制三角形
        glBindVertexArray(vertex_array_object);                                    // 绑定VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);                                          // 绘制三角形
        glBindVertexArray(0);                                                      // 解除绑定
 
        // 交换缓冲并且检查是否有触发事件(比如键盘输入、鼠标移动等）
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    // 删除VAO和VBO
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_object);
 
    // 清理所有的资源并正确退出程序
    glfwTerminate();
    return 0;
}
