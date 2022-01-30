#pragma once


#include <TextureSet.hpp>

#include <Pacman.hpp>

#include <SFML/Graphics.hpp>


using namespace sf;


enum struct MenuState {
    PLAY, SETTINGS, QUIT
};


class Menu {
private:

    RenderWindow* window;
    TextureSet texture_set;

    MenuState menu_state;

    Sprite* title_sprite;
    Sprite* title_choice_sprite;


public:

    Menu();
    ~Menu();

    void setWindow(RenderWindow* window_in);

    void moveMenu(const Orientation orientation);
    void draw();
    void reset();

    MenuState getState();


};

