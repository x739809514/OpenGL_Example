#pragma once
#include <string>


struct ShaderProgram
{
    std::string vertex;
    std::string fragment;
};

class Shader
{
private:
    unsigned int renderID;
    std::string filePath;
public:
    Shader(std::string path);
    ~Shader();

    void Bind();
    void UnBind();

    void SetUniform4f(int location, float v0, float v1, float f0, float f1);
    int GetLocationOfUniform(const std::string& name);
    unsigned int CompileShader(unsigned int type, std::string &source);
    unsigned int CreateShader(std::string &vertextShader, std::string &fragmentShader);
    ShaderProgram ParseShader();
};
