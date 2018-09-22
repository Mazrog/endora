//
// Created by mazrog on 17/04/18.
//

#ifndef ENDORA_TEXTURE_HPP
#define ENDORA_TEXTURE_HPP

#include <vector>

class Texture {
public:
    Texture(GLenum type = GL_TEXTURE_2D);
    ~Texture();

    Texture& operator=(Texture const&) = delete;
    Texture(Texture const&) = delete;

    Texture(Texture && text);
    Texture& operator=(Texture && text);


    unsigned int generate_texture();

    unsigned int load_texture_to_vram(const char *image_path,
                                      GLenum internal_format, GLenum format);

    unsigned int load_cubemap_to_vram(const char *folder_path,
                                      GLenum internal_format, GLenum format);

    void bind() const;
    void bind(GLuint index) const;
    void send(unsigned index, int slot = 0) const;
    void disable();

    bool is_active() const { return !_ids.empty(); }

private:
    GLenum                  _type;
    std::vector<GLuint>     _ids;
};

#endif
