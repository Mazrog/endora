//
// Created by mazrog on 17/04/18.
//

#include <GL/glew.h>
#include <endora/texture.hpp>
#include <endora/utils.hpp>

Texture::Texture(GLenum type) : _type(type) {}

Texture::~Texture() {
    for(auto const& id : _ids) {
        if (id) {
            glDeleteTextures(1, &id);
            get_error("Texture deletion");
        }
    }
}

Texture& Texture::operator=(Texture && text) {
    _ids = std::move(text._ids);
    _type = text._type;

    text._ids.clear();
    return *this;
}

Texture::Texture(Texture &&text)
        : _type(text._type),
          _ids(std::move(text._ids)) {
    text._ids.clear();
}

unsigned int Texture::generate_texture() {
    GLuint texture;
    glGenTextures(1, &texture);      get_error("Texture generation");
    _ids.push_back(texture);

    return _ids.size()-1;
}

unsigned int Texture::load_texture_to_vram(unsigned width, unsigned height, void * pixels, GLenum format) {
    generate_texture();
    bind();

    glTexImage2D(_type, 0, format,
                 width,
                 height, 0,
                 format, GL_UNSIGNED_BYTE, pixels);
    get_error("tex image 2D");

    glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");

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
    glBindTexture(_type, _ids.at(index)); get_error("Texture binding");
}

void Texture::send(unsigned index, int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);    get_error("Texture active");
    bind(index);
}

void Texture::disable() {
    glBindTexture(_type, 0);    get_error("disable texture");
}


