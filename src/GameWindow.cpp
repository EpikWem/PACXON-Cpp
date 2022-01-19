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
            movePacman(Orientation::UP);
        if (keyboard_manager.testCommand(Commands::DOWN))
            movePacman(Orientation::DOWN);
        if (keyboard_manager.testCommand(Commands::RIGHT))
            movePacman(Orientation::RIGHT);
        if (keyboard_manager.testCommand(Commands::LEFT))
            movePacman(Orientation::LEFT);
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
    /*for (uint i = 0; i < TILEMAP_DIMX*TILEMAP_DIMY; i++)
        window->draw(*tilemap_sprites[i]);*/
    //window->draw(getSprite(Sprites::FOREGROUND));
    for (uint y = 0; y < tilemap.getDimy(); y++) {
        for (uint x = 0; x < tilemap.getDimx(); x++) {
            tile_sprite->setPosition(x*CELL_SIZE, y*CELL_SIZE);
            switch (tilemap.getCellState(x, y)) {
                case CellState::VOID:
                    tile_sprite->setTexture(*texture_set.getTexture(Textures::VOID));
                    break;
                case CellState::WALL:
                    tile_sprite->setTexture(*texture_set.getTexture(Textures::WALL));
                    break;
                case CellState::PATH:
                    tile_sprite->setTexture(*texture_set.getTexture(Textures::PATH));
                    break;
                case CellState::PATH_R:
                    tile_sprite->setTexture(*texture_set.getTexture(Textures::PATH_R));
                    break;
            }
            window->draw(*tile_sprite);
        }
    }
}


void GameWindow::draw() {
    window->draw(getSprite(Sprites::BACKGROUND));
    switch (game_state) {
        case GameState::GAME:
            drawTilemap();
            updatePacmanSprite();
            window->draw(getSprite(Sprites::PACMAN));
            break;
        case GameState::GAMEOVER:
            window->draw(getSprite(Sprites::GAMEOVER));
        default:
            break;
    }
}


void GameWindow::movePacman(const Orientation orientation) {
    pacman.move(orientation);
    switch (tilemap.getCellState(pacman.x, pacman.y)){
        case CellState::VOID:
            tilemap.setCellState(pacman.x, pacman.y, CellState::PATH);
            pacman.running = true;
            break;
        case CellState::WALL:
            pacman.running = false;
            break;
        case CellState::PATH:
        case CellState::PATH_R:
            gameOver();
            break;
    }
    
}


void GameWindow::updatePacmanSprite() {
    sprites[Sprites::PACMAN]->setRotation(pacman.getOrientationDegre());
    sprites[Sprites::PACMAN]->setPosition(pacman.x*CELL_SIZE+CELL_SIZE/2, pacman.y*CELL_SIZE+CELL_SIZE/2);
}


void GameWindow::loop() {
    timer += clock.getElapsedTime().asSeconds();
    clock.restart();

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

    if (game_state == GameState::GAME && pacman.running)
        if (compter >= 3) {
            movePacman(pacman.orientation);
            compter = 0;
        } else
            compter++;

    window->clear();
    draw();
    window->display();

    //while (timer < TICK_TIME);
    timer = 0;
}


void GameWindow::gameOver() {
    game_state = GameState::GAMEOVER;
}


GameWindow::GameWindow() {
    compter = 0;
    srand(time(0));
    timer = 0.0f;
    game_state = GameState::GAME;
    fullscreen_mode = false;
    window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "PACXON");
    //window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    tile_sprite = new Sprite();
    sprites[Sprites::BACKGROUND] = new Sprite(*texture_set.getTexture(Textures::BACKGROUND));
    sprites[Sprites::GAMEOVER] = new Sprite(*texture_set.getTexture(Textures::GAMEOVER));
    sprites[Sprites::PACMAN] = new Sprite(*texture_set.getTexture(Textures::PACMAN));
    sprites[Sprites::PACMAN]->setOrigin(CELL_SIZE/2, CELL_SIZE/2);
}


GameWindow::~GameWindow() {
    delete window;
    delete tile_sprite;
    delete sprites[Sprites::BACKGROUND];
    delete sprites[Sprites::GAMEOVER];
    delete sprites[Sprites::PACMAN];
}


void GameWindow::run() {
    while (window->isOpen())
        loop();
}

