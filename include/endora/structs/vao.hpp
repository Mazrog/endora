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
    ~Vao();

    Vao(Vao const&) = delete;
    Vao& operator=(Vao const &) = delete;

    Vao(Vao && other);
    Vao& operator=(Vao && other);

    void bind();
    void clean();

    void emplace_vbo(GLenum target = GL_ARRAY_BUFFER);

    template < class T >
    void set_data(size_t size, T *data) {
        bind();
        if( size > 0 ) {
            _vbos.back().setBufferData(size, data);
        }
    }

    void format_index_data(GLuint index, int coordinateSize, unsigned stride = 0, void *pointer = NULL) {
        glEnableVertexAttribArray(index);   endora_error("VAO enable vertex index");
        glVertexAttribPointer(index, coordinateSize, GL_FLOAT, GL_FALSE, stride, pointer);    endora_error("VAO vertex pointer");
    }

    /* Getters */
    GLuint getId() const { return _id; }

    std::vector<Vbo> & vbos() { return _vbos; }
    Vbo & vbo() { return _vbos.back(); }

private:
    GLuint                  _id;
    std::vector<Vbo>      _vbos;
};

#endif //ENDORA_VAO_HPP
