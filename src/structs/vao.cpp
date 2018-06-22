//
// Created by mazrog on 22/03/18.
//

#include <endora/structs/vao.hpp>

int Vao::id_current_vao = 0;

void Vao::bind_vao(GLuint const &vao_id) {
    if(static_cast<int>(vao_id) != Vao::id_current_vao) {
        glBindVertexArray(vao_id); get_error("Vao::bind_vao");
        Vao::id_current_vao = vao_id;
    }
}

Vao::Vao() {
    glGenVertexArrays(1, &id); get_error("VAO creation");
}

Vao::~Vao() { clean(); }

Vao::Vao(Vao && vao) : id(vao.id), vbos(std::move(vao.vbos)) { vao.id = 0; }

Vao& Vao::operator=(Vao && vao) {
    id = vao.id;
    vbos = std::move(vao.vbos);
    vao.id = 0;
    vao.vbos.clear();

    return *this;
}

void Vao::bind() {
    Vao::bind_vao(id);
}

void Vao::clean() {
    if(id) {
        for (auto &vbo: vbos) { vbo.clean(); }

        Vao::bind_vao(0);
        get_error("VAO unbinding");
        glDeleteVertexArrays(1, &id);
        get_error("VAO deletion");
    }
}

void Vao::emplace_vbo(GLenum target) {
    bind();
    vbos.emplace_back(target);
}
