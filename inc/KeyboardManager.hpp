#pragma once


#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <map>

using namespace sf;
typedef unsigned int uint;


#define KEYMAP_SIZE 7
#define KEYBOARD_SIZE 101


enum Commands {
    UP, DOWN, RIGHT, LEFT, YES, NO,
    STOP, FULLSCREEN, GRID
};


class KeyboardManager {
private:

    std::map<Commands, Keyboard::Key> keymap;
    bool key_pressed[KEYBOARD_SIZE];


public:

    KeyboardManager();

    void update(const Event event);
    bool testCommand(const Commands command);


};

