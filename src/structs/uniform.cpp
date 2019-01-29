//
// Created by mazrog on 22/03/18.
//

#include <endora/structs/uniform.hpp>

Uniform::Uniform() : progid(0), location(0), name("") {}

Uniform::Uniform(GLuint progid, std::string const& name) {
    load_uniform(progid, name.c_str());
}

Uniform::~Uniform() {
    progid = 0;
    location = 0;
    name.clear();
}

void Uniform::load_uniform(GLuint progID, const char *var_name) {
    if(progID) {
        progid = progID;
        name = var_name;
        ShaderProgram::use(progid);
        location = glGetUniformLocation(progid, name.c_str()); endora_error("current unif location");
    }
}
