#include "Cube.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Cube::Cube() {
    mVAO.Bind();
    mVBO.Bind();
    VAO::SetVec3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetVec3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    VBO<std::uint32_t>::Unbind();
    VAO::Unbind();
}

void Cube::Draw() const {
    mVAO.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<std::int32_t>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));
    VAO::Unbind();
}

void Cube::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
