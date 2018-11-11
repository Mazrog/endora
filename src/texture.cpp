//
// Created by mazrog on 17/04/18.
//

#include <IL/il.h>
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

unsigned int Texture::load_texture_to_vram(const char *image_path, GLenum internal_format, GLenum format) {
    ilInit();
    ILuint src = ilGenImage();
    ilBindImage(src);
    ilLoadImage(image_path);
    ILubyte * surf = ilGetData();

    generate_texture();
    bind();

    glTexImage2D(_type, 0, internal_format,
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT), 0,
                 format, GL_UNSIGNED_BYTE, surf);
    get_error("tex image 2D");

    ilDeleteImage(src);

    glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");

    return _ids.size()-1;
}

unsigned int Texture::load_cubemap_to_vram(const char *folder_path, GLenum internal_format, GLenum format) {
    generate_texture();
    bind();

    const char * file_names[6] = { "right.png", "left.png",
                                   "top.png", "bottom.png",
                                   "back.png", "front.png" };

    ilInit();
    ILuint src = ilGenImage();
    ilBindImage(src);

    char image_name[500];

    for(unsigned i = 0; i < 6; ++i) {
        snprintf(image_name, sizeof(image_name), "%s/%s", folder_path, file_names[i]);

        ilLoadImage(image_name);
        ILubyte *surf = ilGetData();

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format,
                     ilGetInteger(IL_IMAGE_WIDTH),
                     ilGetInteger(IL_IMAGE_HEIGHT), 0,
                     format, GL_UNSIGNED_BYTE, surf);
        get_error("tex image 2D");
    }

    ilDeleteImage(src);

    glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");

    glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(_type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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


