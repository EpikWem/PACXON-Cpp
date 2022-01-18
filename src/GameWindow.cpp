#include <GameWindow.hpp>


Sprite GameWindow::getSprite(const Sprites id) {
    return *sprites[id];
}


void GameWindow::testCommands() {
    if (keyboard_manager.testCommand(Commands::STOP))
        window->close();
    else {
        if (keyboard_manager.testCommand(Commands::FULLSCREEN))
            toggleFullscreen();
        if (keyboard_manager.testCommand(Commands::UP))
            pacman.move(Orientation::UP);
        if (keyboard_manager.testCommand(Commands::DOWN))
            pacman.move(Orientation::DOWN);
        if (keyboard_manager.testCommand(Commands::RIGHT))
            pacman.move(Orientation::RIGHT);
        if (keyboard_manager.testCommand(Commands::LEFT))
            pacman.move(Orientation::LEFT);
    }
    
}


void GameWindow::toggleFullscreen() {
    delete window;
    if (fullscreen_mode)
        window = new RenderWindow(VideoMode(1280, 720), "PACXON");
    else
        window = new RenderWindow(VideoMode(1280, 720), "PACXON", Style::Fullscreen);
    fullscreen_mode = !fullscreen_mode;
}


void GameWindow::drawTilemap() {
    Sprite s;
    for (uint y = 0; y < tilemap.getDimy(); y++) {
        for (uint x = 0; x < tilemap.getDimx(); x++) {
            s.setPosition(x, y);
            switch (tilemap.getCellState(x, y)) {
                case CellState::VOID:
                    s.setTexture(*texture_set.getTexture(Textures::VOID));
                    break;
                case CellState::WALL:
                    s.setTexture(*texture_set.getTexture(Textures::WALL));
                    break;
                case CellState::PATH:
                    s.setTexture(*texture_set.getTexture(Textures::PATH));
                    break;
                case CellState::PATH_R:
                    s.setTexture(*texture_set.getTexture(Textures::PATH_R));
                    break;
            }
            window->draw(s);
        }
    }
}


void GameWindow::draw() {
    window->draw(Sprite(*texture_set.getTexture(Textures::BACKGROUND)));
    //drawTilemap();

    updatePacmanSprite();
    window->draw(getSprite(Sprites::PACMAN));
}


void GameWindow::updatePacmanSprite() {
    sprites[Sprites::PACMAN]->setRotation(pacman.getOrientationDegre());
    sprites[Sprites::PACMAN]->setPosition(pacman.x*CELL_SIZE+CELL_SIZE/2, pacman.y*CELL_SIZE+CELL_SIZE/2);
}


void GameWindow::loop() {
    Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window->close();
                break;
            case Event::KeyPressed:
            case Event::KeyReleased:
                keyboard_manager.update(event);
                testCommands();
                break;
            default:
                break;
        }
    }
    window->clear();
    draw();
    window->display();
}


GameWindow::GameWindow() {
    fullscreen_mode = false;
    window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "PACXON");
    window->setVerticalSyncEnabled(true);
    sprites[Sprites::PACMAN] = new Sprite(*texture_set.getTexture(Textures::PACMAN));
    sprites[Sprites::PACMAN]->setOrigin(CELL_SIZE/2, CELL_SIZE/2);
}


GameWindow::~GameWindow() {
    delete window;
    delete sprites[Sprites::PACMAN];
}


void GameWindow::run() {
    while (window->isOpen())
        loop();
}

