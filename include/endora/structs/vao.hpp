//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_VAO_HPP
#define ENDORA_VAO_HPP

#include <endora/structs/vbo.hpp>

#include <vector>

class Vao {
public:
    static GLuint id_current_vao;
    static void bind_vao(GLuint const& vao_id);

public:
    Vao();
    Vao(size_t nvbos);
    ~Vao();

    Vao(Vao const&) = delete;
    Vao& operator=(Vao const &) = delete;

    Vao(Vao && other);
    Vao& operator=(Vao && other);

    void bind();
    void clean();

    Vbo & emplace_vbo(GLenum target = GL_ARRAY_BUFFER);

    operator GLuint() const { return _id; }
    Vbo & operator[] (unsigned index) { return _vbos[index]; }

private:
    GLuint                  _id;
    std::vector<Vbo>      _vbos;
};

#endif //ENDORA_VAO_HPP
