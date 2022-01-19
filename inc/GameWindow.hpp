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
#define HEIGHT 960
#define CELL_SIZE 40
#define TICK_TIME 0.07


enum struct GameState {
    MENU, PAUSE, GAME, GAMEOVER
};


enum struct Sprites {
    BACKGROUND, GAMEOVER,
    PACMAN, CHERRY, BANANA, ICE, PACGOM
};


class GameWindow {
private:

    RenderWindow* window;
    uint compter;
    float timer;
    Clock clock;
    GameState game_state;
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
    void movePacman(const Orientation orientation);
    void updatePacmanSprite();
    void loop();
    void gameOver();


public:

    GameWindow();
    ~GameWindow();
    void run();


};

