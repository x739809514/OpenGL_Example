#pragma once
#include <string>
#include <unordered_map>

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
    std::unordered_map<std::string, int> m_uniformLocationMap;

public:
    Shader(std::string path);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    void SetUniform4f(int location, float v0, float v1, float f0, float f1);
    void SetUniform1i(const std::string &name, int value);
    void SetUniform1f(const std::string &name, float value);
    int GetLocationOfUniform(const std::string &name);
private:
    unsigned int CompileShader(unsigned int type, std::string &source);
    unsigned int CreateShader(std::string &vertextShader, std::string &fragmentShader);
    ShaderProgram ParseShader();
};
