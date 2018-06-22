//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_VAO_HPP
#define ENDORA_VAO_HPP

#include <endora/structs/vbo.hpp>

#include <vector>

class Vao {
public:
    static unsigned id_current_vao;
    static void bind_vao(GLuint const& vao_id);

public:
    Vao();
    ~Vao();

    Vao(Vao const&) = delete;
    Vao& operator=(Vao const &) = delete;

    Vao(Vao && vao);
    Vao& operator=(Vao && vao);

    void bind();
    void clean();

    void emplace_vbo(GLenum target = GL_ARRAY_BUFFER);

    template < class T >
    void linkDataAttribute(size_t size, T * data) {
        bind();
        if( size > 0 ) {
            vbos.back().setBufferData(size, data);
        }
    }

    void formatDataAttribute(GLuint index, int coordinateSize, unsigned stride = 0, void * pointer = NULL) {
        glEnableVertexAttribArray(index);   get_error("VAO enable vertex index");
        glVertexAttribPointer(index, coordinateSize, GL_FLOAT, GL_FALSE, stride, pointer);    get_error("VAO vertex pointer");
    }

    template < class T >
    void linkElementDataAttribute(size_t size, T * data) {
        bind();
        vbos.back().setBufferData(size, data);
    }


    /* Getters */
    GLuint getId() const { return id; }
    std::vector<Vbo> & getVbos() { return vbos; }

    /* Setters */
    void setId(GLuint new_id) { id = new_id; }

private:
    GLuint                  id;
    std::vector<Vbo>      vbos;
};

#endif //ENDORA_VAO_HPP
