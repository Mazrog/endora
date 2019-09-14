//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_VBO_HPP
#define ENDORA_VBO_HPP

#include "../utils.hpp"

class Vbo {
public:
    static GLuint id_current_vbo;

public:
    Vbo(GLenum type = GL_ARRAY_BUFFER);
    ~Vbo();

    Vbo(Vbo const&) = delete;
    Vbo& operator=(Vbo const &) = delete;

    Vbo(Vbo && from);
    Vbo& operator=(Vbo && from);

    void bind();

    void clean();

    template < class T >
    void buffer_data(size_t size, const T * data, GLenum usage = GL_STATIC_DRAW) {
        glBufferData(_type, size, data, usage);      endora_error("VBO Buffer Data");
    }

    void format_index_data(GLuint index, int coordinateSize, unsigned stride = 0, void *pointer = NULL) {
        glEnableVertexAttribArray(index);   endora_error("VAO enable vertex index");
        glVertexAttribPointer(index, coordinateSize, GL_FLOAT, GL_FALSE, stride, pointer);    endora_error("VAO vertex pointer");
    }

    /*  *
     * size : size in bytes of the buffer data store
     */
    void allocate_storage(size_t size, GLbitfield flags);

    /*  *
     * Returns a pointer to a mapped memory for the buffer data
     */
    template < typename T >
    T * map_buffer_range(GLintptr offset, GLsizeiptr size, GLbitfield access) {
        T * ret = (T *) glMapBufferRange(_type, offset, size, access); endora_error("Vbo Mapping buffer range");
        return ret;
    }

    void unmap_buffer() {
        glUnmapBuffer(_type); endora_error("Vbo UnMapping buffer");
    }


    operator GLuint() const { return _id; }

private:
    GLuint      _id;
    GLenum      _type;
};

#endif //ENDORA_VBO_HPP
