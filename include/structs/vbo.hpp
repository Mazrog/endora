//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_VBO_HPP
#define ENDORA_VBO_HPP

#include "utils.hpp"

class Vbo {
public:
    Vbo(GLenum type = GL_ARRAY_BUFFER);
    ~Vbo();

    Vbo(Vbo const&) = delete;

    void bind();

    void clean();

    template < class T >
    void setBufferData(size_t size, const T * data, GLenum usage = GL_STATIC_DRAW) {
        bind();
        glBufferData(type, size, data, usage);      get_error("VBO Buffer Data");
    }


    GLuint getId() const { return id; }

private:
    GLuint      id;
    GLenum      type;
};

#endif //ENDORA_VBO_HPP
