#include <GameWindow.hpp>


void GameWindow::createGhostsSprites() {
    for (uint i = 0; i < ghosts_number; i++) {
        ghosts[i].second = new Sprite(*texture_set.getTexture(ghosts[i].first.type));
        /*ghosts[i].second->setOrigin(
            ghosts[i].first.x + ghosts[i].first.size/2,
            ghosts[i].first.y + ghosts[i].first.size/2
        );*/
        printf("Created a Ghost with directions (%f, %f)\n", ghosts[i].first.dx, ghosts[i].first.dy);
    }
}


void GameWindow::testCommands() {
    if (keyboard_manager.testCommand(Commands::STOP))
        window->close();
    else {
        if (keyboard_manager.testCommand(Commands::FULLSCREEN))
            toggleFullscreen();
        if (keyboard_manager.testCommand(Commands::GRID))
            toggleGrid();
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
    if (fullscreen_mod)
        window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "PACXON");
    else
        window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "PACXON", Style::Fullscreen);
    fullscreen_mod = !fullscreen_mod;
}


void GameWindow::toggleGrid() {
    grid_mod = !grid_mod;
}


void GameWindow::drawTilemap() {
    for (uint y = 0; y < tilemap.getDimy(); y++) {
        for (uint x = 0; x < tilemap.getDimx(); x++) {
            tile_sprite->setPosition(x*CELL_SIZE, y*CELL_SIZE);
            tile_sprite->setTexture(*texture_set.getTexture(tilemap.getCellState(x, y), grid_mod));
            window->draw(*tile_sprite);
        }
    }
}


void GameWindow::draw() {
    window->draw(*background_sprite);
    switch (game_state) {
        case GameState::GAME:
            drawTilemap();
            updatePacmanSprite();
            updateGhostsSprite();
            window->draw(*pacman_sprite);
            for (uint i = 0; i < ghosts_number; i++)
                window->draw(*ghosts[i].second);
            break;
        case GameState::GAMEOVER:
            window->draw(*gameover_sprite);
        default:
            break;
    }
}


void GameWindow::movePacman(const Orientation orientation) {
    pacman.move(orientation);
    switch (tilemap.getCellState(pacman.x, pacman.y)) {
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
        default:
            break;
    }
    
}


void GameWindow::updatePacmanSprite() {
    pacman_sprite->setRotation(pacman.getOrientationDegre());
    pacman_sprite->setPosition(pacman.x*CELL_SIZE+CELL_SIZE/2, pacman.y*CELL_SIZE+CELL_SIZE/2);
}



void GameWindow::updateGhostsSprite() {
    for (uint i = 0; i < ghosts_number; i++)
        ghosts[i].second->setPosition(
            ghosts[i].first.x - ghosts[i].first.size/2,
            ghosts[i].first.y - ghosts[i].first.size/2);
}


void GameWindow::fillVoid() {
    for (uint i = 0; i < ghosts_number; i++) {
        tilemap.tryLockCells(int(ghosts[i].first.x/CELL_SIZE), int(ghosts[i].first.y/CELL_SIZE));
        /*printf("\nAs ghost placed at (%i,%i) :\n", ghosts[i].first.x, ghosts[i].first.y);
        printf("Gonna lock (%i,%i)\n", int(WIDTH/ghosts[i].first.x), int(HEIGHT/ghosts[i].first.y));
        system("pause");*/
    }
    tilemap.fillVoids();
}


void GameWindow::loop() {
    timer += clock.getElapsedTime().asSeconds();
    clock.restart();

    if (pacman.running) {
        if (compter >= 3) {
            movePacman(pacman.orientation);
            compter = 0;
        } else
            compter++;
    } else
        fillVoid();

    for (uint i = 0; i < ghosts_number; i++)
        ghosts[i].first.move(tilemap);

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

    //while (timer < TICK_TIME);
    timer = 0;
}


void GameWindow::gameOver() {
    game_state = GameState::GAMEOVER;
}


GameWindow::GameWindow() {
    compter = 0;
    timer = 0.0f;
    game_state = GameState::GAME;
    fullscreen_mod = false;
    grid_mod = true;
    
    window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "PACXON");
    //window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    ghosts_number = 2;
    ghosts[0].first = Ghost(GhostType::PINKY);
    ghosts[1].first = Ghost(GhostType::PINKY);
    createGhostsSprites();

    tile_sprite = new Sprite();
    background_sprite = new Sprite(*texture_set.getTexture(Textures::BACKGROUND));
    gameover_sprite = new Sprite(*texture_set.getTexture(Textures::GAMEOVER));
    pacman_sprite = new Sprite(*texture_set.getTexture(Textures::PACMAN));
    pacman_sprite->setOrigin(CELL_SIZE/2, CELL_SIZE/2);
}


GameWindow::~GameWindow() {
    delete window;
    delete tile_sprite;
    delete background_sprite;
    delete gameover_sprite;
    delete pacman_sprite;
    for (uint i = 0; i < 8; i++)
        delete ghosts[i].second;
}


void GameWindow::run() {
    while (window->isOpen())
        loop();
}

