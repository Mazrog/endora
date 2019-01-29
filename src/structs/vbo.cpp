#include <endora/structs/vbo.hpp>

GLuint Vbo::id_current_vbo = 0;

Vbo::Vbo(GLenum type) : _type(type) {
    glGenBuffers(1, &_id); endora_error("VBO creation");
}

Vbo::Vbo(Vbo &&from) : _id(from._id), _type(from._type) { from._id = 0; }

Vbo& Vbo::operator=(Vbo &&from) {
    _id = from._id;
    _type = from._type;

    from._id = 0;
    return *this;
}

Vbo::~Vbo() { clean(); }

void Vbo::clean() {
    if(_id) {
        glDeleteBuffers(1, &_id);
        endora_error("VBO deletion");
        _id = 0;
    }
}

void Vbo::bind() {
    if (_id != Vbo::id_current_vbo) {
        glBindBuffer(_type, _id); endora_error("VBO binding");

        Vbo::id_current_vbo = _id;
    }
}

void Vbo::allocate_storage(size_t size, GLbitfield flags) {
    glBufferStorage(_type, size, NULL, flags); endora_error("VBO storage allocation");
}