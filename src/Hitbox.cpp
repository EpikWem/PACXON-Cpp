#include <Hitbox.hpp>


#include <math.h>


Hitbox::Hitbox() {
    Hitbox(0, 0, 0, 0);
}


Hitbox::Hitbox(const uint origin_x, const uint origin_y, const uint point_x, const uint point_y) {
    if (ox < px || oy < py) {
        return;
    }
    ox = origin_x;
    oy = origin_y;
    px = point_x;
    py = point_y;
}


uint Hitbox::getWidth() const {
    return abs(px - ox);
}


uint Hitbox::getHeight() const {
    return abs(py - oy);
}


bool Hitbox::testCollision(const Hitbox hitbox) {
   return ( ox < hitbox.ox + hitbox.getWidth() &&
            ox + getWidth() > hitbox.ox &&
            oy < hitbox.oy + hitbox.getHeight() &&
            getHeight() + oy > hitbox.oy);
}

