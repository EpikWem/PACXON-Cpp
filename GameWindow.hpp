#pragma once


#include <KeyboardManager.hpp>
#include <TextureSet.hpp>
#include <Tilemap.hpp>
#include <Pacman.hpp>

#include <SFML/Graphics.hpp>

#include <map>


using namespace sf;
typedef unsigned int uint;


#define WIDTH 1280
#define HEIGHT 720
#define CELL_SIZE 40


enum struct Sprites {
    PACMAN, CHERRY, BANANA, ICE, PACGOM
};


class GameWindow {
private:

    RenderWindow* window;
    bool fullscreen_mode;
    KeyboardManager keyboard_manager;
    TextureSet texture_set;
    Tilemap tilemap;
    Pacman pacman;
    std::map<Sprites, Sprite*> sprites;

    Sprite getSprite(const Sprites id);
    void testCommands();
    void toggleFullscreen();
    void drawTilemap();
    void draw();
    void updatePacmanSprite();
    void loop();


public:

    GameWindow();
    ~GameWindow();
    void run();


};

