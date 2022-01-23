#include <GameWindow.hpp>


void GameWindow::testCommands() {
    if (keyboard_manager.testCommand(Commands::STOP))
        close();
    else {

        if (keyboard_manager.testCommand(Commands::FULLSCREEN))
            toggleFullscreen();

        switch (game_state) {
            case GameState::GAME:
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
                break;
            case GameState::MENU:
                if (keyboard_manager.testCommand(Commands::UP))
                    moveMenu(Orientation::UP);
                if (keyboard_manager.testCommand(Commands::DOWN))
                    moveMenu(Orientation::DOWN);
                if (keyboard_manager.testCommand(Commands::YES)) {
                    if (menu_state == MenuState::PLAY)
                        displayGame();
                    else if (menu_state == MenuState::QUIT)
                        close();
                }
                break;
            default:
                break;
        }

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


//=============================================================================


void GameWindow::displayMenu() {
    game_state = GameState::MENU;
    menu_state = MenuState::PLAY;
}


void GameWindow::displayGame() {
    game_state = GameState::GAME;
}


void GameWindow::displayGameOver() {
    game_state = GameState::GAMEOVER;
}


//=============================================================================


void GameWindow::moveMenu(const Orientation orientation) {
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
    uint ims = (menu_state == MenuState::PLAY ? 0 : (menu_state == MenuState::SETTINGS ? 1 : 2));
    title_choice_sprite->setPosition(
        WIDTH/2 - 420/2,
        416 + 81*ims);
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
            displayGameOver();
            break;
        default:
            break;
    }
}


void GameWindow::updatePacmanSprite() {
    pacman_sprite->setRotation(pacman.getOrientationDegre());
    pacman_sprite->setPosition(
        pacman.x*CELL_SIZE + CELL_SIZE/2,
        pacman.y*CELL_SIZE + CELL_SIZE/2);
}



void GameWindow::updateGhostsSprite() {
    for (uint i = 0; i < ghosts_number; i++)
        ghosts[i].second->setPosition(
            ghosts[i].first.x,
            ghosts[i].first.y);
}


//=============================================================================


void GameWindow::fillVoid() {
    for (uint i = 0; i < ghosts_number; i++) {
        tilemap.tryLockCells(
            uint((ghosts[i].first.x) / CELL_SIZE),
            uint((ghosts[i].first.y) / CELL_SIZE));
    }
    tilemap.fillVoids();
}


void GameWindow::reloadScore() {
    score = tilemap.getFillingScore();
}


//=============================================================================


void GameWindow::updateDatas() {
    if (game_state == GameState::GAME) {

        if (pacman.running) {
            if (compter >= 3) {
                movePacman(pacman.orientation);
                compter = 0;
            } else
                compter++;
        } else {
            fillVoid();
            reloadScore();
        }

        for (uint i = 0; i < ghosts_number; i++)
            ghosts[i].first.move(tilemap);

    }
}


void GameWindow::triggerEvents() {
    Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                close();
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
}


//=============================================================================


void GameWindow::drawTilemap() {
    for (uint y = 0; y < tilemap.getDimy(); y++) {
        for (uint x = 0; x < tilemap.getDimx(); x++) {
            tile_sprite->setPosition(x*CELL_SIZE, y*CELL_SIZE);
            tile_sprite->setTexture(*texture_set.getTexture(tilemap.getCellState(x, y), grid_mod));
            window->draw(*tile_sprite);
            
            if (tilemap.getCellState(x, y) == CellState::PATH_R)
                if (pacman.kill())
                    displayGameOver();
        }
    }
}


void GameWindow::draw() {
    switch (game_state) {
        case GameState::MENU:
            window->draw(*title_sprite);
            window->draw(*title_choice_sprite);
            break;
        case GameState::GAME:
            window->draw(*background_sprite);
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


//=============================================================================


GameWindow::GameWindow() {
    // init basic vars:
    compter = 0;
    timer = 0.0f;
    game_state = GameState::MENU;
    menu_state = MenuState::PLAY;
    fullscreen_mod = false;
    grid_mod = true;
    score = 0;
    returned_to_wall = true;
    
    // init window:
    window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "PACXON");
    window->setFramerateLimit(60);

    // init ghosts:
    ghosts_number = 2;
    ghosts[0].first = Ghost(GhostType::PINKY);
    ghosts[1].first = Ghost(GhostType::PINKY);
    for (uint i = 0; i < ghosts_number; i++) {
        ghosts[i].second = new Sprite(*texture_set.getTexture(ghosts[i].first.type));
        ghosts[i].second->setOrigin(ghosts[i].first.size/2, ghosts[i].first.size/2);
    }

    //init pacman:
    pacman_sprite = new Sprite(*texture_set.getTexture(Textures::PACMAN));
    pacman_sprite->setOrigin(CELL_SIZE/2, CELL_SIZE/2);

    // init other sprites:
    tile_sprite = new Sprite();
    background_sprite = new Sprite(*texture_set.getTexture(Textures::BACKGROUND));
    title_sprite = new Sprite(*texture_set.getTexture(Textures::TITLE));
    title_choice_sprite = new Sprite(*texture_set.getTexture(Textures::TITLE_CHOICE));
    gameover_sprite = new Sprite(*texture_set.getTexture(Textures::GAMEOVER));
}


GameWindow::~GameWindow() {
    delete window;
    delete tile_sprite;
    delete background_sprite;
    delete title_sprite;
    delete title_choice_sprite;
    delete gameover_sprite;
    delete pacman_sprite;
    for (uint i = 0; i < 8; i++)
        delete ghosts[i].second;
}


void GameWindow::run() {
    moveMenu(Orientation::RIGHT);
    while (window->isOpen()) {

        // UPDATE TIMER
        timer += clock.getElapsedTime().asSeconds();
        clock.restart();

        triggerEvents();
        updateDatas();

        // UPDATE WINDOW
        window->clear();
        draw();
        window->display();

    }
}


void GameWindow::close() {
    game_state = GameState::STOP;
    window->close();
}

