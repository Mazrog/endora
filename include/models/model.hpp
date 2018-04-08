//
// Created by mazrog on 25/03/18.
//

#ifndef ENDORA_MODEL_HPP
#define ENDORA_MODEL_HPP

#include "common.hpp"

class Model {
public:
    Model();
    Model(const char * filePath);

    ~Model();

    void clear();

private:
    vecf    vertices;
    vec2f   uvs;
    vecf    normals;
};

#endif
