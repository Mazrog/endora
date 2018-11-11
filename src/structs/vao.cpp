//
// Created by mazrog on 22/03/18.
//

#include <endora/structs/vao.hpp>

GLuint Vao::id_current_vao = 0;

void Vao::bind_vao(GLuint const &vao_id) {
    if(vao_id != Vao::id_current_vao) {
        glBindVertexArray(vao_id); get_error("Vao::bind_vao");
        Vao::id_current_vao = vao_id;
    }
}

Vao::Vao() {
    glGenVertexArrays(1, &id); get_error("VAO creation");
}

Vao::~Vao() {
    clean();
}

Vao::Vao(Vao && other) : id(other.id), vbos(std::move(other.vbos)) {
    other.id = 0;
    other.vbos.clear();
}

Vao& Vao::operator=(Vao && other) {
    id = other.id;
    vbos = std::move(other.vbos);
    other.id = 0;
    other.vbos.clear();

    return *this;
}

void Vao::bind() {
    Vao::bind_vao(id);
}

void Vao::clean() {
    if(id) {
        for (auto &vbo: vbos) { vbo.clean(); }

        Vao::bind_vao(0); get_error("VAO unbinding");
        glDeleteVertexArrays(1, &id); get_error("VAO deletion");

        id = 0;
    }
}

void Vao::emplace_vbo(GLenum target) {
    bind();
    vbos.emplace_back(target);
}
