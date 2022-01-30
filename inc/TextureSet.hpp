#pragma once


#include <Ghost.hpp>
#include <Tilemap.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include <string.h>


using namespace sf;
typedef unsigned int uint;


const std::string IMAGES_FOLDER = "../res/images";


enum struct Textures {
    BACKGROUND, TITLE, TITLE_CHOICE, GAMEOVER, WIN,
    PACMAN, BLINKY, INKY, PINKY, CLYDE,
    CHERRY, BANANA, STRAWBERRY, PACGUM,
    VOID, WALL, PATH, PATH_R, TRUE_VOID
};


class TextureSet {
private:

    std::map<Textures, Texture*> textures;

    Texture* loadTexture(const char file[]);
    Texture* loadTexture(const char pack[], const char file[]);


public:

    TextureSet();
    ~TextureSet();

    Texture* getTexture(const Textures id);
    Texture* getTexture(const CellState cell_state, const bool grid_mod);
    Texture* getTexture(const GhostType ghost_type);


};

