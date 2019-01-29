//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_UNIFORM_HPP
#define ENDORA_UNIFORM_HPP

#include <endora/utils.hpp>
#include <endora/program.hpp>

#include <string>

#ifndef ENDORA_CUSTOM_TYPES
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace {
    using vec2 = glm::vec2;
    using vec3 = glm::vec3;
    using mat4 = glm::mat4;

    const float * value_ptr(mat4 const& mat) {
        return glm::value_ptr(mat);
    }
}

#endif // ENDORA_CUSTOM_TYPES


/* Sending function template */
template <typename T>
inline void send_uniform(GLint const& loc, T const&, unsigned count = 0);

template <>
inline void send_uniform<int>(GLint const& loc, int const& f, unsigned) {
    glUniform1i(loc, f); endora_error("send int");
}

template <>
inline void send_uniform<float>(GLint const& loc, float const& f, unsigned) {
    glUniform1f(loc, f); endora_error("send float");
}

template <>
inline void send_uniform<mat4>(GLint const& loc, mat4 const& m, unsigned) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, ::value_ptr(m)); endora_error("send mat");
}

template <>
inline void send_uniform<vec2>(GLint const& loc, vec2 const& v, unsigned) {
    glUniform2f(loc, v[0], v[1]); endora_error("send vec3");
}

template <>
inline void send_uniform<vec3>(GLint const& loc, vec3 const& v, unsigned) {
    glUniform3f(loc, v[0], v[1], v[2]); endora_error("send vec3");
}

template <>
inline void send_uniform<int *>(GLint const& loc, int * const& p, unsigned count) {
    glUniform1iv(loc, count, p); endora_error("send int *");
}

/* ################################################################################## */

struct Uniform {
    Uniform();
    Uniform(GLuint progid, std::string const& name);

    ~Uniform();

    void load_uniform(GLuint progID, const char *var_name);

    /* ---------- */
    Uniform(Uniform const&) = delete;
    Uniform& operator=(Uniform const&) = delete;

    Uniform(Uniform && unif) = default;
    Uniform& operator=(Uniform && unif) = default;
    /* ------------ */

    template < typename T >
    void send(T const& t, unsigned count = 0) const {
        /* Use the correct program */
        ShaderProgram::use(progid);
        send_uniform(location, t, count);
    }

    GLuint      progid;
    GLint       location;
    std::string name;
};

#endif //ENDORA_UNIFORM_HPP
