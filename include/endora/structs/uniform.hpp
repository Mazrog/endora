//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_UNIFORM_HPP
#define ENDORA_UNIFORM_HPP

#include <endora/utils.hpp>
#include <endora/structs/program.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>


/* Sending function template */
template <typename T>
inline void send_uniform(GLint const& loc, T const&, unsigned count = 0);

template <>
inline void send_uniform<int>(GLint const& loc, int const& f, unsigned) {
    glUniform1i(loc, f); get_error("send int");
}

template <>
inline void send_uniform<float>(GLint const& loc, float const& f, unsigned) {
    glUniform1f(loc, f); get_error("send float");
}

template <>
inline void send_uniform<glm::mat4>(GLint const& loc, glm::mat4 const& m, unsigned) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m)); get_error("send mat");
}

template <>
inline void send_uniform<glm::vec2>(GLint const& loc, glm::vec2 const& v, unsigned) {
    glUniform2f(loc, v.x, v.y); get_error("send vec3");
}

template <>
inline void send_uniform<glm::vec3>(GLint const& loc, glm::vec3 const& v, unsigned) {
    glUniform3f(loc, v.x, v.y, v.z); get_error("send vec3");
}

template <>
inline void send_uniform<int *>(GLint const& loc, int * const& p, unsigned count) {
    glUniform1iv(loc, count, p); get_error("send int *");
}

/* ################################################################################## */

struct Uniform {
    Uniform();
    Uniform(GLuint progid, std::string const& name);

    ~Uniform();

    void loadUniform(GLuint progID, const char * var_name);

    /* ---------- */
    Uniform(Uniform const&) = delete;
    Uniform& operator=(Uniform const&) = delete;

    Uniform(Uniform && unif);
    Uniform& operator=(Uniform && unif);
    /* ------------ */

    template < typename T >
    void send(T const& t, unsigned count = 0) const {
        /* Use the correct program */
        ShaderProgram::useProgram(progid);
        send_uniform(location, t, count);
    }

    GLuint      progid;
    GLint       location;
    std::string name;
};

#endif //ENDORA_UNIFORM_HPP
