#pragma once


typedef unsigned int uint;


enum struct Orientation { RIGHT, DOWN, LEFT, UP };


class Pacman {
public:

    uint x, y;
    bool running;
    Orientation orientation;
    uint lives;

    Pacman();

    void move(const Orientation direction);

    float getOrientationDegre();

    // return TRUE if no more lives
    bool kill();


};

