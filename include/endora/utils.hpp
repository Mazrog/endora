#ifndef ENDORA_UTILS_HPP
#define ENDORA_UTILS_HPP

#include <iostream>
#include <GL/glew.h>

#define endora_error(message, ...) \
    endora::get_error(__FILE__, __LINE__, message, ##__VA_ARGS__)


namespace endora {
    template < typename ... Args >
    void get_error(const char * file, int line, const char * message, Args &&... args) {
        GLenum err;
        if((err = glGetError() ) != GLEW_OK){
            std::cerr << "ENDORA OPENGL ERROR -------- " << message << "\nCalled from " << file << " at line " << line << '\n';
            std::cerr << "Error (" << err << ") : " << glewGetErrorString(err) << " -- " << gluErrorString(err) << '\n';
            if constexpr (sizeof...(args)) {
                ((std::cerr << args << " "), ...) << '\n' << std::endl;
            }
        }
    }
}

#endif
