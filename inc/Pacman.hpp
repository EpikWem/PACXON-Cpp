#pragma once


typedef unsigned int uint;


enum struct Orientation { RIGHT, DOWN, LEFT, UP };


class Pacman {
public:

    uint x, y;
    Orientation orientation;

    Pacman();

    void move(const Orientation direction);

    float getOrientationDegre() {
        return int(orientation)*90.0f;
    }


};

