#include <Pacman.hpp>


#include <Tilemap.hpp>


Pacman::Pacman() {
    x = 0;
    y = 0;
    running = false;
    orientation = Orientation::RIGHT;
}


void Pacman::move(const Orientation direction) {
    uint lx = x, ly = y;
    switch (direction) {
        case Orientation::UP:
            y--;
            break;
        case Orientation::DOWN:
            y++;
            break;
        case Orientation::RIGHT:
            x++;
            break;
        case Orientation::LEFT:
            x--;
            break;
    }
    if (x > TILEMAP_DIMX-1)
        x = lx;
    if (y > TILEMAP_DIMY-1)
        y = ly;
    orientation = direction;
}

