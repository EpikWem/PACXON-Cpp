#pragma once


#include <Tilemap.hpp>

#include <cstdlib>


typedef unsigned int uint;


enum struct GhostType {
    PINKY, INKY, CLYDE, BLINKY
};


class Ghost {
public:

    GhostType type;
    uint x, y;
    float speed;
    float dx, dy;
    uint size;

    Ghost();
    Ghost(const GhostType type);

    void move(const Tilemap tilemap);


};

