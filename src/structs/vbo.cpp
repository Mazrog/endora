#include <endora/structs/vbo.hpp>

GLuint Vbo::id_current_vbo = 0;

Vbo::Vbo(GLenum type) : type(type) {
    glGenBuffers(1, &id); endora_error("VBO creation");
}

Vbo::Vbo(Vbo &&from) : id(from.id), type(from.type) { from.id = 0; }

Vbo& Vbo::operator=(Vbo &&from) {
    id = from.id;
    type = from.type;

    from.id = 0;
    return *this;
}

Vbo::~Vbo() { clean(); }

void Vbo::clean() {
    if(id) {
        glDeleteBuffers(1, &id);
        endora_error("VBO deletion");
        id = 0;
    }
}

void Vbo::bind() {
    if (id != Vbo::id_current_vbo) {
        glBindBuffer(type, id); endora_error("VBO binding");

        Vbo::id_current_vbo = id;
    }
}

void Vbo::allocateStorage(size_t size, GLbitfield flags) {
    bind();
    glBufferStorage(type, size, NULL, flags); endora_error("VBO storage allocation");
}