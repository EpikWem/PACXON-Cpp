#include <Ghost.hpp>


#include <GameWindow.hpp>


int genDirection() {
    int d = 0;
    while(d == 0)
        d = 4 - rand()%8;
    return d;
}


Ghost::Ghost() {
    Ghost(GhostType::PINKY);
}

Ghost::Ghost(const GhostType ghost_type) {
    type = ghost_type;
    x = 2*CELL_SIZE + rand()%(WIDTH - 2*CELL_SIZE);
    y = 2*CELL_SIZE + rand()%(HEIGHT - 2*CELL_SIZE);
    dx = genDirection();
    dy = genDirection();
    switch (type) {
        case GhostType::PINKY:
            speed = 2.0f;
            size = CELL_SIZE;
            break;
        case GhostType::INKY:
            speed = 1.2f;
            size = CELL_SIZE;
            break;
        case GhostType::CLYDE:
            speed = 1.6f;
            size = CELL_SIZE;
            break;
        case GhostType::BLINKY:
            speed = 0.8f;
            size = CELL_SIZE*1.2f;
            break;
    }
}


void Ghost::move(Tilemap &tilemap) {
    x+= dx*speed;
    uint tx = uint(x/CELL_SIZE);
    uint ty = uint(y/CELL_SIZE);
    if (tilemap.getCellState(tx, ty) != CellState::VOID) {
        if (tilemap.getCellState(tx, ty) == CellState::PATH)
            tilemap.setCellState(tx, ty, CellState::PATH_R);
        dx = -dx;
        x+= dx*speed;
    }

    y+= dy*speed;
    ty = uint(y/CELL_SIZE);
    if (tilemap.getCellState(tx, ty) != CellState::VOID) {
        if (tilemap.getCellState(tx, ty) == CellState::PATH)
            tilemap.setCellState(tx, ty, CellState::PATH_R);
        dy = -dy;
        y+= dy*speed;
    }
}

