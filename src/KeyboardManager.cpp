#include <KeyboardManager.hpp>


KeyboardManager::KeyboardManager() {
    for (uint i = 0; i < KEYBOARD_SIZE; i++)
        key_pressed[i] = false;
    keymap[Commands::UP] = Keyboard::Key::Up;
    keymap[Commands::DOWN] = Keyboard::Key::Down;
    keymap[Commands::RIGHT] = Keyboard::Key::Right;
    keymap[Commands::LEFT] = Keyboard::Key::Left;
    keymap[Commands::YES] = Keyboard::Key::Enter;
    keymap[Commands::NO] = Keyboard::Key::BackSpace;
    keymap[Commands::STOP] = Keyboard::Key::F9;
    keymap[Commands::FULLSCREEN] = Keyboard::Key::F11;
    keymap[Commands::GRID] = Keyboard::Key::G;
}


void KeyboardManager::update(const Event event) {
    key_pressed[event.key.code] = (event.type == Event::KeyPressed);
}


bool KeyboardManager::testCommand(const Commands command) {
    return key_pressed[keymap[command]];
}

