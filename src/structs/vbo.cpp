#include <endora/structs/vbo.hpp>

Vbo::Vbo(GLenum type) : type(type) {
    glGenBuffers(1, &id); get_error("VBO creation");
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
        get_error("VBO deletion");
    }
}

void Vbo::bind() {
    glBindBuffer(type, id);  get_error("VBO binding");
}