//
// Created by mazrog on 08/07/18.
//

#ifndef PROJECT_FBO_HPP
#define PROJECT_FBO_HPP

#include <GL/glew.h>
#include <vector>

class Fbo {

public:
    static void default_fbo();

public:
    Fbo();
    ~Fbo();

    void clean();
    void bind() const;

    void add_depth_attachement(unsigned width = 2048, unsigned height = 2048);
    void bind_texture_slot(unsigned target, unsigned slot = 0) const;

    /* ------------------- */
    Fbo(Fbo const&) = delete;
    Fbo & operator=(Fbo const&) = delete;

    Fbo(Fbo && other);
    Fbo & operator=(Fbo && other);

private:
    GLuint                  _id;

    /* Vector containing all texture ids attached to the fbo */
    std::vector<GLuint>     _attachments;
};


#endif
