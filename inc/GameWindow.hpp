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
#define TICK_TIME 0.07


enum struct Sprites {
    BACKGROUND,
    PACMAN, CHERRY, BANANA, ICE, PACGOM
};


class GameWindow {
private:

    RenderWindow* window;
    float timer;
    Clock clock;
    bool fullscreen_mode;
    KeyboardManager keyboard_manager;
    TextureSet texture_set;
    Tilemap tilemap;
    Pacman pacman;
    std::map<Sprites, Sprite*> sprites;
    Sprite* tile_sprite;

    Sprite getSprite(const Sprites id);
    void testCommands();
    void toggleFullscreen();
    void drawTilemap();
    void draw();
    void updatePacmanSprite();
    void updateTilemapSprites();
    void loop();


public:

    GameWindow();
    ~GameWindow();
    void run();


};

