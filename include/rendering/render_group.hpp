//
// Created by mazrog on 12/05/18.
//

#ifndef ENDORA_RENDER_GROUP_HPP
#define ENDORA_RENDER_GROUP_HPP

#include <vector>

template < typename Object >
class RenderGroup {
public:
    RenderGroup();
    ~RenderGroup();

    void add(Object * object);

    void render() const;

private:
    std::vector<Object *>   objects;
};

#include "render_group.tpp"

#endif
