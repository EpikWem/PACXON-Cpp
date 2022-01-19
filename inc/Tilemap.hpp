#pragma once


typedef unsigned int uint;


#define TILEMAP_DIMX 32
#define TILEMAP_DIMY 18


enum struct CellState {
    VOID, WALL, PATH, PATH_R
};


class Tilemap {
private:
    
    CellState grid[TILEMAP_DIMX*TILEMAP_DIMY];


public:

    Tilemap();
    Tilemap(const uint p_dimx, const uint p_dimy);

    CellState getCellState(const uint x, const uint y);

    uint getDimx() const;
    uint getDimy() const;


};

