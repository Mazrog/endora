//
// Created by mazrog on 07/07/18.
//

#include "endora/include/endora/drawable.hpp"

Drawable::Drawable() : _is_visible(true) {}

Drawable::~Drawable() {}

bool Drawable::visible() const {
    return _is_visible;
}