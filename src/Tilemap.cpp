#include <Tilemap.hpp>


#include <stdio.h>
#include <cstdlib>


uint getCoord(const uint x, const uint y) {
    return (y*TILEMAP_DIMX + x);
}


Tilemap::Tilemap() {
    for (uint y = 0; y < TILEMAP_DIMY; y++) {
        for (uint x = 0; x < TILEMAP_DIMX; x++) {
            if (x == 0 || y == 0 || x == TILEMAP_DIMX-1 || y == TILEMAP_DIMY-1)
                grid[getCoord(x, y)] = CellState::WALL;
            else
                grid[getCoord(x, y)] = CellState::VOID;
        }
    }
}


void Tilemap::tryLockCells(const uint x, const uint y) {
    if (getCellState(x, y) == CellState::VOID) {
        setCellState(x, y, CellState::LOCK);
        tryLockCells(x-1, y);
        tryLockCells(x+1, y);
        tryLockCells(x, y-1);
        tryLockCells(x, y+1);
    }
}


void Tilemap::fillVoids() {
    for (uint y = 0; y < TILEMAP_DIMY; y++) {
        for (uint x = 0; x < TILEMAP_DIMX; x++) {
            if (getCellState(x, y) != CellState::LOCK)
                grid[getCoord(x, y)] = CellState::WALL;
            else
                grid[getCoord(x, y)] = CellState::VOID;
        }
    }
            
}


CellState Tilemap::getCellState(const uint x, const uint y) {
    return grid[getCoord(x, y)];
}


void Tilemap::setCellState(const uint x, const uint y, CellState new_state) {
    grid[getCoord(x, y)] = new_state;
}


uint Tilemap::getDimx() const { return TILEMAP_DIMX; }
uint Tilemap::getDimy() const { return TILEMAP_DIMY; }

