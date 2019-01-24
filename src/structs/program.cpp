//
// Created by mazrog on 22/03/18.
//

#include <endora/structs/program.hpp>

/* ------------------------------------------------------------------------------ */

Shader::Shader(const char * file, GLenum type) : type(type), file(file) {
    compile();
}

Shader::~Shader() {
    glDeleteShader(id); get_error("delete shader");
}

void Shader::compile() {
    /* Variables */
    int compiled; // results of shader compilation

    /* Reading source code */
    GLchar * shaderSource = filetobuf(file);

    /* Shader creation */
    id = glCreateShader(type); get_error("create shader");
    glShaderSource(id, 1, (const GLchar**)&shaderSource, nullptr); get_error("source");
    glCompileShader(id); get_error("compile");

    /* Compilation errors test */
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled); get_error("log - 1");
    if (!compiled) {
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); get_error("log - 2");
        char * log_msg = new char[length];
        glGetShaderInfoLog(id, length, &length, log_msg); get_error("log - 3");
        std::cerr << "Compilation : " << type << " Shader Error => " << log_msg << std::endl;
        delete [] log_msg;
        return;
    }
    delete [] shaderSource;
}

/* ------------------------------------------------------------------------------ */

unsigned ShaderProgram::id_current_prog = 0;

void ShaderProgram::use(GLuint prog_id) {
    if(static_cast<unsigned>(prog_id) != ShaderProgram::id_current_prog) {
        glUseProgram(prog_id); get_error("using prog");
        ShaderProgram::id_current_prog = prog_id;
    }
}


ShaderProgram::ShaderProgram() : _prog_id(0) {}

ShaderProgram::~ShaderProgram() {
    destroy();
}

void ShaderProgram::destroy() {
    if(_prog_id) {
        glDeleteProgram(_prog_id);
        get_error("Deleting program");
        _prog_id = 0;
    }
}

void ShaderProgram::attach_shader(Shader & shader) {
    glAttachShader(_prog_id, shader.id); get_error("attach");
}

void ShaderProgram::detach_shader(Shader & shader) {
    glDetachShader(_prog_id, shader.id); get_error("detach");
}

void ShaderProgram::link() {
    /* Variables */
    int linked; // result of linking shaders to program

    glLinkProgram(_prog_id); get_error("link prog");

    /* Linking errors test */
    glGetProgramiv(_prog_id, GL_LINK_STATUS, &linked); get_error("prog log - 1");
    if (!linked){
        int log_length;
        glGetProgramiv(_prog_id, GL_INFO_LOG_LENGTH, &log_length); get_error("prog log - 1");
        char * log_msg = new char[log_length];
        glGetProgramInfoLog(_prog_id, log_length, &log_length, log_msg);
        std::cerr << "Linking : Program Error => " << log_msg << std::endl;
        delete [] log_msg;
        return;
    }

    use(_prog_id);
}

GLuint ShaderProgram::getProgId() const {
    return _prog_id;
}

void ShaderProgram::use() {
    use(_prog_id);
}