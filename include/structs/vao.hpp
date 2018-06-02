//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_VAO_HPP
#define ENDORA_VAO_HPP

#include <structs/vbo.hpp>

#include <vector>

class Vao {
public:
    Vao();
    ~Vao();

    Vao(Vao const&) = delete;
    Vao& operator=(Vao const &) = delete;

    Vao(Vao && vao);
    Vao& operator=(Vao && vao);

    void bind();
    void clean();


    template < class T >
    void linkDataAttribute(GLuint index, int coordinateSize, size_t size, T * data) {
        bind();
        vbos.emplace_back();
        if( size > 0 ) {
            vbos.back().setBufferData(size, data);
        }

        glEnableVertexAttribArray(index);   get_error("VAO enable vertex index");
        glVertexAttribPointer(index, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void *) 0);    get_error("VAO vertex pointer");
    }

    template < class T >
    void linkElementDataAttribute(size_t size, T * data) {
        bind();
        vbos.emplace_back(GL_ELEMENT_ARRAY_BUFFER);
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
