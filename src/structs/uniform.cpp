//
// Created by mazrog on 22/03/18.
//

#include <endora/structs/uniform.hpp>

Uniform::Uniform() : progid(0), location(0), name("") {}

Uniform::Uniform(GLuint progid, std::string const& name) : progid(progid), location(), name(name) {
    load_uniform(progid, name.c_str());
}

Uniform::~Uniform() {
    progid = 0;
    location = 0;
    name.clear();
}

Uniform::Uniform(Uniform && unif) :
        progid(unif.progid),
        location(unif.location),
        name(unif.name) {
    unif.progid = 0;
    unif.location = 0;
    unif.name.clear();
}

Uniform& Uniform::operator=(Uniform && unif) {
    progid = unif.progid;
    location = unif.location;
    name = unif.name;

    unif.progid = 0;
    unif.location = 0;
    unif.name.clear();

    return *this;
}

void Uniform::load_uniform(GLuint progID, const char *var_name) {
    if(progID) {
        progid = progID;
        name = var_name;
        ShaderProgram::use(progid);
        location = glGetUniformLocation(progid, name.c_str()); endora_error("current unif location");
    }
}
