#include <Pacman.hpp>


#include <Tilemap.hpp>


Pacman::Pacman() {
    x = 0;
    y = 0;
    running = false;
    orientation = Orientation::RIGHT;
    lives = 3;
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


float Pacman::getOrientationDegre() {
    return int(orientation)*90.0f;
}


bool Pacman::kill() {
    x = 0; y = 0;
    lives--;
    if (lives <= 0)
        return true;
    else
        return false;
}

