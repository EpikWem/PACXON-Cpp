#pragma once


#include <KeyboardManager.hpp>
#include <TextureSet.hpp>
#include <Tilemap.hpp>
#include <Pacman.hpp>
#include <Ghost.hpp>

#include <SFML/Graphics.hpp>

#include <map>


using namespace sf;
typedef unsigned int uint;


#define WIDTH 1280
#define HEIGHT 960
#define CELL_SIZE 40
#define TICK_TIME 0.07f


enum struct GameState {
    MENU, PAUSE, GAME, GAMEOVER, STOP
};

enum struct MenuState {
    PLAY, SETTINGS, QUIT
};


class GameWindow {
private:


    RenderWindow* window;
    uint compter;
    float timer;
    Clock clock;

    GameState game_state;
    MenuState menu_state;

    bool fullscreen_mod;
    bool grid_mod;
    uint score;
    bool returned_to_wall;

    KeyboardManager keyboard_manager;
    TextureSet texture_set;
    Tilemap tilemap;

    Pacman pacman;
    std::pair<Ghost, Sprite*> ghosts[8];
    uint ghosts_number;

    Sprite* background_sprite;
    Sprite* title_sprite;
    Sprite* title_choice_sprite;
    Sprite* gameover_sprite;
    Sprite* pacman_sprite;
    Sprite* tile_sprite;


    void testCommands();
    void toggleFullscreen();
    void toggleGrid();

    void displayMenu();
    void displayGame();
    void displayGameOver();

    void moveMenu(const Orientation orientation);
    void movePacman(const Orientation orientation);
    void updatePacmanSprite();
    void updateGhostsSprite();

    void fillVoid();
    void reloadScore();

    void updateDatas();
    void triggerEvents();

    void drawTilemap();
    void draw();


public:


    GameWindow();
    ~GameWindow();

    void run();
    void close();


};

