//
// Created by mazrog on 22/03/18.
//

#include <endora/structs/uniform.hpp>

Uniform::Uniform(GLuint progid, std::string const& name) : progid(progid), location(), name(name) {
    loadUniform(progid, name.c_str());
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
    unif.name = nullptr;
}

Uniform& Uniform::operator=(Uniform && unif) {
    progid = unif.progid;
    location = unif.location;
    name = unif.name;

    unif.progid = 0;
    unif.location = 0;
    unif.name = nullptr;

    return *this;
}

void Uniform::loadUniform(GLuint progID, const char * var_name) {
    if(progID) {
        progid = progID;
        name = var_name;
        ShaderProgram::useProgram(progid);
        location = glGetUniformLocation(progid, name.c_str()); get_error("current unif location");
    }
}