#pragma once

#include <glm/glm.hpp>

class Shader {
public:
    Shader(const char *vShaderSource, const char *fShaderSource);
    void Use() const;
    void Delete() const;
    void SetFloat(const char *name, float s) const;
    void SetVec2(const char *name, const glm::vec2 &v) const;
    void SetVec3(const char *name, const glm::vec3 &v) const;
    void SetVec4(const char *name, const glm::vec4 &v) const;
    void SetMat2(const char *name, const glm::mat2 &m) const;
    void SetMat3(const char *name, const glm::mat3 &m) const;
    void SetMat4(const char *name, const glm::mat4 &m) const;
    [[nodiscard]] static Shader LoadFromFile(const char *vShaderPath, const char *fShaderPath);

private:
    std::int32_t mProgram = 0;
};
