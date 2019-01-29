//
// Created by mazrog on 17/04/18.
//

#ifndef ENDORA_TEXTURE_HPP
#define ENDORA_TEXTURE_HPP

#include <vector>
#include <GL/glew.h>

class Texture {
public:
    Texture(GLenum type = GL_TEXTURE_2D);
    ~Texture();

    Texture& operator=(Texture const&) = delete;
    Texture(Texture const&) = delete;

    Texture(Texture && text) = default;
    Texture& operator=(Texture && text) = default;

    unsigned int load_texture_to_vram(unsigned width, unsigned height, void * pixels, GLenum format);

    unsigned int generate_texture();

    void bind() const;
    void bind(GLuint index) const;
    void send(unsigned index, int slot = 0) const;
    void disable();

    operator bool() const { return !_ids.empty(); }

private:
    GLenum                  _type;
    std::vector<GLuint>     _ids;
};

#endif
