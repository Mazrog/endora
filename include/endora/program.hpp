//
// Created by mazrog on 22/03/18.
//

#ifndef ENDORA_SHADERPROGRAM_HPP
#define ENDORA_SHADERPROGRAM_HPP

#include <endora/utils.hpp>

struct Shader {
    Shader(const char * file, GLenum type);
    ~Shader();

    void compile();

	GLenum type;
	const char * file;
    GLuint id;
};


class ShaderProgram {
public:
    static unsigned id_current_prog;
    static void use(GLuint prog_id);

public:
    ShaderProgram();

    template < typename ... Shaders >
    explicit ShaderProgram(Shaders && ... shaders) {
        static_assert( (std::is_same_v<Shader, Shaders> && ...) , "All arguments must be of \"Shader\" type.");

        /* Program creation */
        _prog_id = glCreateProgram(); endora_error("create prog");

        (attach_shader(shaders), ...);
        link();
        (detach_shader(shaders), ...);
    }

    ~ShaderProgram();

    /* ###################################################################################### */
    /* Deleting the copy operators */
    ShaderProgram(ShaderProgram const&) = delete;
    ShaderProgram& operator=(ShaderProgram const&) = delete;

    /* Move constructors + move operators */
    ShaderProgram(ShaderProgram && program) : _prog_id(program._prog_id) { program._prog_id = 0; }
    ShaderProgram& operator=(ShaderProgram && program) {
        _prog_id = program._prog_id;
        program._prog_id = 0;
        return *this;
    }

    /* ###################################################################################### */

    void attach_shader(Shader & shader);
    void detach_shader(Shader & shader);

    void link();

    void use();

    void destroy();

    /* Getters and Setters */
    GLuint id() const;

private:
    GLuint _prog_id;
};

#endif
