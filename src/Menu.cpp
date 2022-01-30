#include <Menu.hpp>


#include <GameWindow.hpp>





Menu::Menu() { 
    window = nullptr;
    menu_state = MenuState::PLAY;
    title_sprite = new Sprite(*texture_set.getTexture(Textures::TITLE));
    title_choice_sprite = new Sprite(*texture_set.getTexture(Textures::TITLE_CHOICE));
}


Menu::~Menu() {
    delete title_sprite;
    delete title_choice_sprite;
}


void Menu::setWindow(RenderWindow* window_in) {
    window = window_in;
}


void Menu::moveMenu(const Orientation orientation) {
    if (orientation == Orientation::DOWN || orientation == Orientation::UP) {
        switch (menu_state) {
            case MenuState::PLAY:
                if (orientation == Orientation::DOWN)
                    menu_state = MenuState::SETTINGS;
                break;
            case MenuState::SETTINGS:
                if (orientation == Orientation::UP)
                    menu_state = MenuState::PLAY;
                else
                    menu_state = MenuState::QUIT;
                break;
            case MenuState::QUIT:
                if (orientation == Orientation::UP)
                    menu_state = MenuState::SETTINGS;
                break;
            default:
                break;
        }
    }
    uint ims = (getState() == MenuState::PLAY ? 0 : (getState() == MenuState::SETTINGS ? 1 : 2));
    title_choice_sprite->setPosition(
        WIDTH/2 - 420/2,
        416 + 81*ims);
}


void Menu::draw() {
    window->draw(*title_sprite);
    window->draw(*title_choice_sprite);
}


void Menu::reset() {
    menu_state = MenuState::PLAY;
}


MenuState Menu::getState() {
    return menu_state;
}

