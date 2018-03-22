//
// Created by mazrog on 22/03/18.
//

#include <endora/utils.hpp>

void get_error(const char * t) {
    GLenum err;
    if((err = glGetError() ) != GLEW_OK){
        std::cerr << t << std::endl;
        std::cerr << "Erreur OpenGL (" << err << ") : " << glewGetErrorString(err) << " -- " << gluErrorString(err) << std::endl;
    }
}

char * filetobuf(const char *file) {
    FILE * fptr;
    long length;
    char * buf;

    if(!(fptr = fopen(file, "rb"))){
        throw std::runtime_error("Shader source file not found !");
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