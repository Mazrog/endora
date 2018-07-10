//
// Created by mazrog on 08/07/18.
//

#include <endora/utils.hpp>
#include "endora/include/endora/structs/fbo.hpp"

void Fbo::default_fbo() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   get_error("Binding default framebuffer");
}

Fbo::Fbo() {
    glGenFramebuffers(1, &_id); get_error("Creating FrameBuffer");
}

Fbo::~Fbo() {
    clean();
}

void Fbo::clean() {
    if (_id) {
        glDeleteFramebuffers(1, &_id); get_error("Deleting FrameBuffers");
        _id = 0;

        for (unsigned const& id : _attachments) {
            glDeleteTextures(1, &id);   get_error("Deleting textures attachments");
        }
    }
}

void Fbo::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, _id); get_error("Binding FrameBuffers");
}

void Fbo::add_depth_attachement(unsigned int width, unsigned int height) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float border_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

    _attachments.push_back(texture_id);

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _id, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

void Fbo::bind_texture_slot(unsigned int slot) const {
    glBindTexture(GL_TEXTURE_2D, _attachments.at(slot));    get_error("Binding attachment texture");
    glActiveTexture(GL_TEXTURE0);   get_error("Activate texture 0");
}

Fbo::Fbo(Fbo &&other) : _id(other._id) {
    other._id = 0;
}

Fbo& Fbo::operator=(Fbo &&other) {
    _id = other._id;
    other._id = 0;

    _attachments = std::move(other._attachments);
    other._attachments.clear();

    return *this;
}