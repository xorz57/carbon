#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const GLchar *vShaderSource, const GLchar *fShaderSource) {
    GLint success;

    const GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, nullptr);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vShader, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
        std::cerr << infoLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, nullptr);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fShader, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
        std::cerr << infoLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vShader);
    glAttachShader(mProgram, fShader);
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(mProgram, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(mProgram, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
        std::cerr << infoLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glDetachShader(mProgram, vShader);
    glDetachShader(mProgram, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

Shader Shader::LoadFromFile(const char *vShaderPath, const char *fShaderPath) {
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.open(vShaderPath);
    fShaderFile.open(fShaderPath);

    std::stringstream vShaderStream;
    std::stringstream fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    const std::string vShaderText = vShaderStream.str();
    const std::string fShaderText = fShaderStream.str();

    const GLchar *vShaderSource = vShaderText.c_str();
    const GLchar *fShaderSource = fShaderText.c_str();

    return {vShaderSource, fShaderSource};
}

void Shader::Use() const {
    glUseProgram(mProgram);
}

void Shader::Delete() const {
    glDeleteProgram(mProgram);
}

void Shader::SetFloat(const char *name, float s) const {
    glUniform1f(glGetUniformLocation(mProgram, name), s);
}

void Shader::SetVec2(const char *name, const glm::vec2 &v) const {
    glUniform2fv(glGetUniformLocation(mProgram, name), 1, glm::value_ptr(v));
}

void Shader::SetVec3(const char *name, const glm::vec3 &v) const {
    glUniform3fv(glGetUniformLocation(mProgram, name), 1, glm::value_ptr(v));
}

void Shader::SetVec4(const char *name, const glm::vec4 &v) const {
    glUniform4fv(glGetUniformLocation(mProgram, name), 1, glm::value_ptr(v));
}

void Shader::SetMat3(const char *name, const glm::mat3 &m) const {
    glUniformMatrix3fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::SetMat4(const char *name, const glm::mat4 &m) const {
    glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE, glm::value_ptr(m));
}
