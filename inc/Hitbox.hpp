#pragma once


typedef unsigned int uint;


class Hitbox {
public:

    uint ox, oy; // origin point
    uint px, py; // second point

    Hitbox();
    Hitbox(const uint origin_x, const uint origin_y, const uint point_x, const uint point_y);

    uint getWidth() const;
    uint getHeight() const;

    bool testCollision(const Hitbox hitbox);


};

