#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

#include <iostream>

enum class ShaderType
{
    None = -1,
    Vertex = 0,
    Fragment = 1,
};

Shader::Shader(std::string path) : filePath(path), renderID(0)
{
    ShaderProgram program = ParseShader();
    renderID = CreateShader(program.vertex,program.fragment);
}

Shader::~Shader()
{
    glDeleteShader(renderID);
}

void Shader::Bind()
{
    glUseProgram(renderID);
}

void Shader::UnBind()
{
    glUseProgram(0);
}


int Shader::GetLocationOfUniform(const std::string& name)
{
    int location = glGetUniformLocation(renderID, name.c_str());
    return location;
}

void Shader::SetUniform4f(int location, float v0, float f0, float f1, float f2)
{
    if (location != -1)
    {
        glUniform4f(location, v0, f0, f1, f2);
    }
}

ShaderProgram Shader::ParseShader()
{
    std::ifstream inFile(filePath);
    std::string line;
    ShaderType type = ShaderType::None;
    std::stringstream ss[2];

    while (getline(inFile, line))
    {
        if (line.find("#Shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                // get vertex str
                type = ShaderType::Vertex;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                // get fragment str
                type = ShaderType::Fragment;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    inFile.close();
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *str = source.c_str();
    glShaderSource(id, 1, &str, NULL);
    glCompileShader(id);

    // Error handing
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *info = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, info);
        std::cout << "Error: " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << "Shader Compiled Failed!" << info << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(std::string &vertextShader, std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertextShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}