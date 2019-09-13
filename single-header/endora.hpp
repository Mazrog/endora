//
// Created by Maxime.Cabanal-Duvil on 9/6/2019.
//

#ifndef ENDORA_SINGLE_HEADER_HPP
#define ENDORA_SINGLE_HEADER_HPP

#include <cstdio>
#include <iostream>
#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef endora_error
#define endora_error(message, ...) \
    ::get_error(__FILE__, __LINE__, message, ##__VA_ARGS__)

namespace {
    template < typename ... Args >
    void get_error(const char * file, int line, const char * message, Args &&... args) {
        GLenum err;
        if((err = glGetError() ) != GLEW_OK){
            std::cerr << "ENDORA OPENGL ERROR -------- " << message << "\nCalled from " << file << " at line " << line << '\n'
                << "Error (" << err << ") : " << glewGetErrorString(err) << " -- " << gluErrorString(err) << '\n';
            if constexpr (sizeof...(args)) {
                ((std::cerr << args << " "), ...) << std::endl;
            }
        }
    }
}

#endif

// Implementation of basic opengl structs

namespace endora::ecs {

using buffer_t = GLuint;
using vertex_array_t = GLuint;
using program_t = GLuint;
using shader_t = GLuint;
using uniform_t = GLint;
using type_t = GLenum;
using texture_t = GLuint;

/* Utils */
inline
GLchar * filetobuf(const char *file) {
    FILE * fptr;
    long length;
    GLchar * buf;

    if(!(fptr = fopen(file, "rb"))){
        std::cerr << "Shader source file not found !\n";
        std::exit(1);
    }
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    buf = new GLchar[length+1];
    fseek(fptr, 0, SEEK_SET);
    fread(buf, length, 1, fptr);
    fclose(fptr);
    buf[length] = 0;

    return buf;
}
/* ----------------------------- */

// program part
inline void check_shader_compile_status(shader_t shader, type_t type) {
    int compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); endora_error("getting shader compile status");
    if (!compiled) {
        int length = 0;
        GLchar * log_msg = nullptr;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length); endora_error("shader log length");
        log_msg = new GLchar[length];
        glGetShaderInfoLog(shader, length, &length, log_msg); endora_error("log - getting log message");
        std::cerr << "Compilation : " << type << " Shader Error => " << log_msg << '\n';
        delete [] log_msg;
    }
}

inline shader_t create_shader(type_t type, char const * filename) {
    shader_t shader = glCreateShader(type); endora_error("creating shader");
    GLchar * source = filetobuf(filename);
    glShaderSource(shader, 1, &source, nullptr); endora_error("specifying source");
    glCompileShader(shader); endora_error("compiling shader");
    delete [] source;

    check_shader_compile_status(shader, type);
    return shader;
}

inline void destroy_shader(shader_t shader) { glDeleteShader(shader); endora_error("destroying shader"); }

template < typename ... Shaders >
void attach_shaders(program_t program, shader_t shader, Shaders && ... shaders) {
    static_assert( (std::is_same_v<shader_t, std::decay_t<Shaders>> && ...), "attach_shaders arguments need to be of shader_t type");
    glAttachShader(program, shader); endora_error("attaching shader");

    if constexpr (sizeof...(Shaders)) {
        ( (glAttachShader(program, shaders), endora_error("")), ...);
    }
}

template < typename ... Shaders >
void detach_shaders(program_t program, shader_t shader, Shaders && ... shaders) {
    static_assert( (std::is_same_v<shader_t, std::decay_t<Shaders>> && ...), "detach_shaders arguments need to be of shader_t type");
    glDetachShader(program, shader); endora_error("detaching shader");

    if constexpr (sizeof...(Shaders)) {
        ( (glDetachShader(program, shaders), endora_error("detaching shader")), ...);
    }
}

inline void link_program(program_t program) { glLinkProgram(program); endora_error("linking program"); }

inline void check_program_link_status(program_t program) {
    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked); endora_error("getting program link status");
    if (!linked){
        int log_length;
        GLchar * log_msg = nullptr;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length); endora_error("program log length");
        log_msg = new GLchar[log_length];
        glGetProgramInfoLog(program, log_length, &log_length, log_msg);
        std::cerr << "Linking : Program Error => " << log_msg << '\n';
        delete [] log_msg;
    }
}

template < typename ... Shaders >
program_t create_program(Shaders && ... shaders) {
    static_assert( sizeof...(Shaders) && (std::is_same_v<shader_t, std::decay_t<Shaders>> && ...), "create_program needs at least one argument of shader_t type");

    program_t program = glCreateProgram(); endora_error("creating program");
    attach_shaders(program, shaders...);
    link_program(program);
    check_program_link_status(program);
    detach_shaders(program, shaders...);
    return program;
}

inline void destroy_program(program_t program) { glDeleteProgram(program); endora_error("destroying program"); }

inline void use_program(program_t program) { glUseProgram(program); endora_error("using program"); }

inline void check_use_program(program_t program) {
    static program_t s_current_program = -1;
    if (program != s_current_program) {
        use_program(program);
    }
}

// vbo part
inline buffer_t create_buffer() {
    buffer_t buffer;
    glGenBuffers(1, &buffer); endora_error("creating buffer");
    return buffer;
}

inline void create_buffers(buffer_t * buffers, std::size_t n) {
    glGenBuffers(n, buffers); endora_error("creating buffers");
}

inline void destroy_buffer(buffer_t buffer) { glDeleteBuffers(1, &buffer); endora_error("destroying buffer"); }

inline void bind_buffer(buffer_t buffer, type_t type) { glBindBuffer(type, buffer); endora_error("bind buffer"); }

inline void check_bind_buffer(buffer_t buffer, type_t type) {
    static buffer_t s_current_buffer = -1;
    if (buffer != s_current_buffer) {
        bind_buffer(buffer, type);
    }
}

template < typename T >
void set_buffer_data(type_t type, std::size_t size, T const * data, type_t usage) {
    glBufferData(type, size, data, usage); endora_error("Setting buffer data");
}

inline void format_buffer_index_data(GLuint index, int coordinate_size, type_t type, unsigned stride, void * pointer) {
    glEnableVertexAttribArray(index); endora_error("enable vertex attrib array");
    glVertexAttribPointer(index, coordinate_size, type, GL_FALSE, stride, pointer); endora_error("vertex attrib pointer format");
}

inline void allocate_buffer_storage(type_t type, std::size_t size, GLbitfield flags) {
    glBufferStorage(type, size, nullptr, flags); endora_error("allocating buffer storage");
}

template < typename T >
T * map_buffer_range(type_t type, GLintptr offset, std::size_t size, GLbitfield access) {
    return static_cast<T *>(glMapBufferRange(type, offset, size, access));
}

inline void unmap_buffer(type_t type) { glUnmapBuffer(type); endora_error("unmapping buffer"); }

// vertex array
inline vertex_array_t create_vertexarray() {
    vertex_array_t vertex_array;
    glGenVertexArrays(1, &vertex_array); endora_error("creating vertex array");
    return vertex_array;
}

inline void destroy_vertex_array(vertex_array_t vertex_array) { glDeleteVertexArrays(1, &vertex_array); endora_error("destroying vertex array"); }

inline void bind_vertex_array(vertex_array_t vertex_array) { glBindVertexArray(vertex_array); endora_error("binding vertex array"); }

inline void check_bind_vertex_array(vertex_array_t vertex_array) {
    static vertex_array_t s_current_vertexarray = -1;
    if (vertex_array != s_current_vertexarray) {
        bind_vertex_array(vertex_array);
    }
}

// uniform

/* This function does not affect current gl_program, so be sure to use the program before */
inline uniform_t create_uniform(program_t program, char const * name) {
    uniform_t location = glGetUniformLocation(program, name); endora_error("getting uniform location: ", name);
    return location;
}

/* These functions do not affect current gl_program, so be sure to use the program before */
inline void send_uniform(uniform_t uniform, int value) { glUniform1i(uniform, value); endora_error("sending uniform int value"); }
inline void send_uniform(uniform_t uniform, float value) { glUniform1f(uniform, value); endora_error("sending uniform float value"); }
inline void send_uniform(uniform_t uniform, glm::vec2 value) { glUniform2f(uniform, value[0], value[1]); endora_error("sending uniform vec2 value"); }
inline void send_uniform(uniform_t uniform, glm::vec3 value) { glUniform3f(uniform, value[0], value[1], value[2]); endora_error("sending uniform vec3 value"); }
inline void send_uniform(uniform_t uniform, glm::mat4 value) { glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value)); endora_error("sending uniform mat4 value"); }

// texture
inline texture_t create_texture() {
    texture_t texture;
    glGenTextures(1, &texture); endora_error("creating texture");
    return texture;
}

inline void destroy_texture(texture_t texture) { glDeleteTextures(1, &texture); endora_error("destroying texture"); }

inline void bind_texture(texture_t texture, type_t target) { glBindTexture(target, texture); endora_error("bind texture"); }

inline void load_2D_surface(type_t target, unsigned width, unsigned height, void * pixels, type_t internal_format, type_t format, type_t type) {
    glTexImage2D(target, 0, internal_format, width, height, 0, format, type, pixels);
    endora_error("Setting texture surface");
}

inline void bind_texture_slot(texture_t texture, type_t target, int slot) {
    glActiveTexture(GL_TEXTURE0 + slot); endora_error("activating texture slot ", slot);
    bind_texture(texture, target);
}

}

#endif //FRESHWIND_ENDORA_HPP
