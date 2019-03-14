//
// Created by mazrog on 22/03/18.
//

#include <endora/program.hpp>

static char * filetobuf(const char *file) {
    FILE * fptr;
    long length;
    char * buf;

    if(!(fptr = fopen(file, "rb"))){
        std::cerr << "Shader source file not found !\n";
        std::exit(1);
    }
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    buf = new char[length+1];
    fseek(fptr, 0, SEEK_SET);
    fread(buf, length, 1, fptr);
    fclose(fptr);
    buf[length] = 0;

    return buf;
}

/* ------------------------------------------------------------------------------ */

Shader::Shader(const char * file, GLenum type) : type(type), file(file) {
    compile();
}

Shader::~Shader() {
    glDeleteShader(id); endora_error("delete shader");
}

void Shader::compile() {
    /* Variables */
    int compiled; // results of shader compilation

    /* Reading source code */
    GLchar * shaderSource = filetobuf(file);

    /* Shader creation */
    id = glCreateShader(type); endora_error("create shader");
    glShaderSource(id, 1, (const GLchar**)&shaderSource, nullptr); endora_error("source");
    glCompileShader(id); endora_error("compile");

    /* Compilation errors test */
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled); endora_error("log - 1");
    if (!compiled) {
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); endora_error("log - 2");
        char * log_msg = new char[length];
        glGetShaderInfoLog(id, length, &length, log_msg); endora_error("log - 3");
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
        glUseProgram(prog_id); endora_error("using prog");
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
        endora_error("Deleting program");
        _prog_id = 0;
    }
}

void ShaderProgram::attach_shader(Shader & shader) {
    glAttachShader(_prog_id, shader.id); endora_error("attach");
}

void ShaderProgram::detach_shader(Shader & shader) {
    glDetachShader(_prog_id, shader.id); endora_error("detach");
}

void ShaderProgram::link() {
    /* Variables */
    int linked; // result of linking shaders to program

    glLinkProgram(_prog_id); endora_error("link prog");

    /* Linking errors test */
    glGetProgramiv(_prog_id, GL_LINK_STATUS, &linked); endora_error("prog log - 1");
    if (!linked){
        int log_length;
        glGetProgramiv(_prog_id, GL_INFO_LOG_LENGTH, &log_length); endora_error("prog log - 1");
        char * log_msg = new char[log_length];
        glGetProgramInfoLog(_prog_id, log_length, &log_length, log_msg);
        std::cerr << "Linking : Program Error => " << log_msg << std::endl;
        delete [] log_msg;
        return;
    }

    use(_prog_id);
}

GLuint ShaderProgram::id() const {
    return _prog_id;
}

void ShaderProgram::use() {
    use(_prog_id);
}