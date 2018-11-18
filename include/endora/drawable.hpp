//
// Created by mazrog on 07/07/18.
//

#ifndef PROJECT_DRAWABLE_HPP
#define PROJECT_DRAWABLE_HPP


class Drawable {
public:
    Drawable();
    virtual ~Drawable() = 0;

    virtual void update() = 0;
    virtual void render() const = 0;

    bool visible() const;

protected:
    bool    _is_visible;
};


#endif
