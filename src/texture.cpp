//
// Created by mazrog on 17/04/18.
//

#include <endora/texture.hpp>
#include <endora/utils.hpp>

Texture::Texture(GLenum type) : _type(type) {}

Texture::~Texture() {
    for(auto const& id : _ids) {
        if (id) {
            glDeleteTextures(1, &id);
            endora_error("Texture deletion");
        }
    }
}

unsigned int Texture::generate_texture() {
    GLuint texture;
    glGenTextures(1, &texture);      endora_error("Texture generation");
    _ids.push_back(texture);

    return _ids.size()-1;
}

unsigned int Texture::load_texture_to_vram(unsigned width, unsigned height, void * pixels, GLenum internal_format, GLenum format) {
    generate_texture();
    bind();

    glTexImage2D(_type, 0, internal_format,
                 width,
                 height, 0,
                 format, GL_UNSIGNED_BYTE, pixels);
    endora_error("tex image 2D");

    glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR); endora_error("mipmap linear");
    glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); endora_error("texture param MAG");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float border_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

    return _ids.size()-1;
}

void Texture::bind() const {
    bind(_ids.size()-1);
}

void Texture::bind(GLuint index) const {
    glBindTexture(_type, _ids.at(index)); endora_error("Texture binding");
}

void Texture::send(unsigned index, int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);    endora_error("Texture active");
    bind(index);
}

void Texture::disable() {
    glBindTexture(_type, 0);    endora_error("disable texture");
}


