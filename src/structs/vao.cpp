//
// Created by mazrog on 22/03/18.
//

#include <endora/structs/vao.hpp>

GLuint Vao::id_current_vao = 0;

void Vao::bind_vao(GLuint const &vao_id) {
    if(vao_id != Vao::id_current_vao) {
        glBindVertexArray(vao_id); endora_error("Vao::bind_vao");
        Vao::id_current_vao = vao_id;
    }
}

Vao::Vao() {
    glGenVertexArrays(1, &_id); endora_error("VAO creation");
}

Vao::Vao(size_t nvbos) : Vao() {
    _vbos.reserve(nvbos);
}

Vao::~Vao() {
    clean();
}

Vao::Vao(Vao && other) : _id(other._id), _vbos(std::move(other._vbos)) {
    other._id = 0;
    other._vbos.clear();
}

Vao& Vao::operator=(Vao && other) {
    _id = other._id;
    _vbos = std::move(other._vbos);
    other._id = 0;
    other._vbos.clear();

    return *this;
}

void Vao::bind() {
    Vao::bind_vao(_id);
}

void Vao::clean() {
    if(_id) {
        for (auto &vbo: _vbos) { vbo.clean(); }

        Vao::bind_vao(0); endora_error("VAO unbinding");
        glDeleteVertexArrays(1, &_id); endora_error("VAO deletion");

        _id = 0;
    }
}

Vbo & Vao::emplace_vbo(GLenum target) {
    return _vbos.emplace_back(target);
}
