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
    renderID = CreateShader(program.vertex, program.fragment);
}

Shader::~Shader()
{
    glDeleteShader(renderID);
}

void Shader::Bind() const
{
    glUseProgram(renderID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

int Shader::GetLocationOfUniform(const std::string &name)
{
    if (m_uniformLocationMap.find(name) != m_uniformLocationMap.end())
    {
        return m_uniformLocationMap[name];
    }
    int location = glGetUniformLocation(renderID, name.c_str());
    if (location == -1)
    {
        std::cout << "warning: uniform" << name << "doesn't exits !" << std::endl;
    }
    else
    {
        m_uniformLocationMap[name] = location;
    }

    return location;
}

void Shader::SetUniform4f(int location, float v0, float f0, float f1, float f2)
{
    if (location != -1)
    {
        glUniform4f(location, v0, f0, f1, f2);
    }
}

void Shader::SetUniform1i(const std::string & name, int value)
{
    glUniform1i(GetLocationOfUniform(name),value);
}

void Shader::SetUniform1f(const std::string & name, float value)
{
    glUniform1f(GetLocationOfUniform(name),value);
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