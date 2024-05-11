#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char *texturePath) {
    glGenTextures(1, &mID);
    glBindTexture(GL_TEXTURE_2D, mID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int texture_w, texture_h;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *pixels = stbi_load(texturePath, &texture_w, &texture_h, nullptr, STBI_rgb_alpha);
    if (pixels) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_w, texture_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *) pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(pixels);
    }
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() const {
    glDeleteTextures(1, &mID);
}