#include <TextureSet.hpp>


Texture* TextureSet::loadTexture(const char file[]) {
    return loadTexture("default", file);
}

Texture* TextureSet::loadTexture(const char pack[], const char file[]) {
    std::string path = IMAGES_FOLDER + "/" + pack + "/" + file + ".png";
    Texture* texture = new Texture();
    if(!texture->loadFromFile(path)) {
        printf("\nERROR: Failed to load texture\n\n");
        system("exit");
    }
    return texture;
}


TextureSet::TextureSet() {
    textures[Textures::BACKGROUND] = loadTexture("background");
    textures[Textures::TITLE] = loadTexture("title");
    textures[Textures::GAMEOVER] = loadTexture("gameover");
    textures[Textures::PACMAN] = loadTexture("pacman");
    textures[Textures::BLINKY] = loadTexture("blinky");
    textures[Textures::INKY] = loadTexture("inky");
    textures[Textures::PINKY] = loadTexture("pinky");
    textures[Textures::CLYDE] = loadTexture("clyde");
    /*textures[Textures::CHERRY] = loadTexture("cherry");
    textures[Textures::BANANA] = loadTexture("banana");
    textures[Textures::ICECREAM] = loadTexture("ice");
    textures[Textures::PACGOM] = loadTexture("pacgom");*/
    textures[Textures::VOID] = loadTexture("void");
    textures[Textures::TRUE_VOID] = loadTexture("true_void");
    textures[Textures::WALL] = loadTexture("wall");
    textures[Textures::PATH] = loadTexture("path");
    textures[Textures::PATH_R] = loadTexture("path_r");
}


TextureSet::~TextureSet() {
    delete textures[Textures::BACKGROUND];
    delete textures[Textures::TITLE];
    delete textures[Textures::GAMEOVER];
    delete textures[Textures::PACMAN];
    delete textures[Textures::BLINKY];
    delete textures[Textures::INKY];
    delete textures[Textures::PINKY];
    delete textures[Textures::CLYDE];
    /*delete textures[Textures::CHERRY];
    delete textures[Textures::BANANA];
    delete textures[Textures::ICECREAM];
    delete textures[Textures::PACGOM];*/
    delete textures[Textures::VOID];
    delete textures[Textures::TRUE_VOID];
    delete textures[Textures::WALL];
    delete textures[Textures::PATH];
    delete textures[Textures::PATH_R];
}


Texture* TextureSet::getTexture(const Textures id) {
    return textures[id];
}

Texture* TextureSet::getTexture(const CellState cell_state, const bool grid_mod) {
    switch (cell_state) {
        case CellState::VOID:
            if (grid_mod)
                return getTexture(Textures::VOID);
            else
                return getTexture(Textures::TRUE_VOID);
            break;
        case CellState::WALL:
            return getTexture(Textures::WALL);
            break;
        case CellState::PATH:
            return getTexture(Textures::PATH);
            break;
        case CellState::PATH_R:
            return getTexture(Textures::PATH_R);
            break;
        default:
            return getTexture(Textures::VOID);
            break;
    }
}

Texture* TextureSet::getTexture(const GhostType ghost_type) {
    switch (ghost_type) {
        case GhostType::PINKY:
            return getTexture(Textures::PINKY);
            break;
        case GhostType::INKY:
            return getTexture(Textures::INKY);
            break;
        case GhostType::CLYDE:
            return getTexture(Textures::CLYDE);
            break;
        case GhostType::BLINKY:
            return getTexture(Textures::BLINKY);
            break;
        default:
            return getTexture(GhostType::PINKY);
    }
}

