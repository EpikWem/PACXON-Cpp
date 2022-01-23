#pragma once


typedef unsigned int uint;


#define TILEMAP_DIMX 32
#define TILEMAP_DIMY 24


enum struct CellState {
    VOID, WALL, PATH, PATH_R, LOCK
};


class Tilemap {
private:
    
    CellState grid[TILEMAP_DIMX*TILEMAP_DIMY];


public:

    Tilemap();
    Tilemap(const uint p_dimx, const uint p_dimy);

    
    void tryLockCells(const uint x, const uint y);
    void fillVoids();
    uint getFillingScore();

    CellState getCellState(const uint x, const uint y);
    void setCellState(const uint x, const uint y, CellState new_state);

    uint getDimx() const;
    uint getDimy() const;


};

