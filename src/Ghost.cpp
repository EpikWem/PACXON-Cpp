#include <Ghost.hpp>


#include <GameWindow.hpp>


float genDirection() {
    switch (rand()%4) {
        case 0:
            return -1.0f;
            break;
        case 1:
            return -0.5f;
            break;
        case 2:
            return 0.5f;
            break;
        case 3:
        default:
            return 1.0f;
            break;
    }
}


Ghost::Ghost() {
    Ghost(GhostType::PINKY);
}

Ghost::Ghost(const GhostType ghost_type) {
    type = ghost_type;
    x = rand()%(WIDTH-CELL_SIZE) + CELL_SIZE;
    y = rand()%(HEIGHT-CELL_SIZE) + CELL_SIZE;
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


void Ghost::move(const Tilemap tilemap) {
    int nx = int(x + dx*speed);
    int ny = int(y + dy*speed);
    if (nx < 0 || nx > TILEMAP_DIMX)
        dx = -dx;
    else
        x = nx;
    if (ny < 0 || ny > TILEMAP_DIMY)
        dy = -dy;
    else
        y = ny;
}

