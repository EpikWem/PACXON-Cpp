#include <Tilemap.hpp>


#include <stdio.h>
#include <cstdlib>


uint getCoord(const uint x, const uint y) {
    if (x >= TILEMAP_DIMX || y >= TILEMAP_DIMY) {
        printf("\nERROR: Gave invalid coordinates to Tilemap.getCellState(): (%i,%i)\n\n", x, y);
        system("pause");
        return 0;
    } else
        return (y*TILEMAP_DIMX + x);
}


Tilemap::Tilemap() {
    for (uint y = 0; y < TILEMAP_DIMY; y++) {
        for (uint x = 0; x < TILEMAP_DIMX; x++) {
            if (x == 0 || y == 0 || x == TILEMAP_DIMX-1 || y == TILEMAP_DIMY-1)
                grid[getCoord(x, y)] = CellState::WALL;
            else
                grid[getCoord(x, y)] = CellState::VOID;
            //printf("%i ", grid[y*dimx + x]);
        }
        //printf("\n");
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

