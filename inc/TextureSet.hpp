#pragma once


#include <SFML/Graphics.hpp>

#include <map>
#include <string.h>

using namespace sf;
typedef unsigned int uint;


const std::string IMAGES_FOLDER = "../res/images";


enum struct Textures {
    BACKGROUND, TITLE, GAMEOVER,
    PACMAN, BLINKY, INKY, PINKY, CLYDE,
    CHERRY, BANANA, ICE, PACGOM,
    VOID, WALL, PATH, PATH_R
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


};

