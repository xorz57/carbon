#include "Capsule.hpp"

Capsule::Capsule() {
    Build(32, 16);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

Capsule::Capsule(const std::uint32_t sectors, const std::uint32_t stacks) {
    Build(sectors, stacks);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Capsule::Build(const std::uint32_t sectors, const std::uint32_t stacks) {
    constexpr float height = 0.5f;

    // Top hemisphere vertices
    for (std::uint32_t stack = 0; stack <= stacks; ++stack) {
        const float stack_step = glm::half_pi<float>() / static_cast<float>(stacks);
        const float stack_angle = static_cast<float>(stack) * stack_step;

        const float y = 0.5f * glm::cos(stack_angle) + height;

        for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
            const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
            const float sector_angle = static_cast<float>(sector) * sector_step;

            const float x = 0.5f * glm::sin(stack_angle) * glm::cos(sector_angle);
            const float z = 0.5f * glm::sin(stack_angle) * glm::sin(sector_angle);

            mVertices.push_back({{x, y, z}});
        }
    }

    // Bottom hemisphere vertices
    for (std::uint32_t stack = 0; stack <= stacks; ++stack) {
        const float stack_step = glm::half_pi<float>() / static_cast<float>(stacks);
        const float stack_angle = glm::half_pi<float>() + static_cast<float>(stack) * stack_step;

        const float y = 0.5f * glm::cos(stack_angle) - height;

        for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
            const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
            const float sector_angle = static_cast<float>(sector) * sector_step;

            const float x = 0.5f * glm::sin(stack_angle) * glm::cos(sector_angle);
            const float z = 0.5f * glm::sin(stack_angle) * glm::sin(sector_angle);

            mVertices.push_back({{x, y, z}});
        }
    }

    // Cylinder vertices
    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
        const float sector_angle = static_cast<float>(sector) * sector_step;

        const float x = 0.5f * glm::cos(sector_angle);
        const float z = 0.5f * glm::sin(sector_angle);

        mVertices.push_back({{x, height, z}});
        mVertices.push_back({{x, -height, z}});
    }

    const std::uint32_t hemisphere_offset = (stacks + 1) * (sectors + 1);

    // Top hemisphere indices
    for (std::uint32_t stack = 0; stack < stacks; ++stack) {
        const std::uint32_t k1 = stack * (sectors + 1);
        const std::uint32_t k2 = k1 + sectors + 1;

        for (std::uint32_t sector = 0; sector < sectors; ++sector) {
            mElements.push_back(k1 + sector);
            mElements.push_back(k2 + sector);
            mElements.push_back(k1 + sector + 1);

            mElements.push_back(k1 + sector + 1);
            mElements.push_back(k2 + sector);
            mElements.push_back(k2 + sector + 1);
        }
    }

    // Bottom hemisphere indices
    for (std::uint32_t stack = 0; stack < stacks; ++stack) {
        const std::uint32_t k1 = hemisphere_offset + stack * (sectors + 1);
        const std::uint32_t k2 = k1 + sectors + 1;

        for (std::uint32_t sector = 0; sector < sectors; ++sector) {
            mElements.push_back(k1 + sector);
            mElements.push_back(k1 + sector + 1);
            mElements.push_back(k2 + sector);

            mElements.push_back(k2 + sector);
            mElements.push_back(k1 + sector + 1);
            mElements.push_back(k2 + sector + 1);
        }
    }

    // Cylinder indices
    const std::uint32_t cylinder_offset = hemisphere_offset * 2;
    for (std::uint32_t sector = 0; sector < sectors; ++sector) {
        const std::uint32_t top1 = cylinder_offset + sector * 2;
        const std::uint32_t top2 = top1 + 1;
        const std::uint32_t bottom1 = top1 + 2;
        const std::uint32_t bottom2 = bottom1 + 1;

        mElements.push_back(top1);
        mElements.push_back(bottom1);
        mElements.push_back(top2);

        mElements.push_back(top2);
        mElements.push_back(bottom1);
        mElements.push_back(bottom2);
    }
}

void Capsule::Draw() const {
    mVAO->Bind();
    mEBO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, nullptr);
    VAO::Unbind();
}

void Capsule::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
