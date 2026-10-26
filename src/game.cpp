#include "../include/game.hpp"

void gameStart(Game& game){
    // list_init(game.spritesheet);

    // Sprite bg;
    // push_back(game.spritesheet, bg);
    // loadSpritesheet(game.spritesheet);

    // AJEITAR DESPUES
    matchStart(game.current_match);

    game.state = PLAYING;
    game.quit = false;
}

void loadSpritesheet(List<Sprite>& spritesheet) {
    
    spritesheet.start->data.texture = LoadTexture("assets/sprites/background.png");
}

void gameProcess(Game& game){
    if (IsKeyPressed(KEY_ESCAPE)) game.quit = true;

    switch(game.state) {

        case MENU:
            // menuProcess();
        break;

        case HOW_TO_PLAY:
            // tutorialProcess();
        break;

        case HISTORY:
            // historyProcess();
        break;

        case SETTINGS:
            // settingsProcess();
        break;

        case PLAYING:
            matchProcess(game.current_match);
        break;

    }
}

void gameOver(Game& game){
    return;
}

void matchStart(Match& match) {

    match.player.pos = (Vector2) {400, 300};

    match.camera = { 0 };

    match.camera.target = { match.player.pos.x + 20, match.player.pos.y + 20 };
    match.camera.offset = { 800 / 2.0f, 450 / 2.0f };
    match.camera.zoom = 1.0f;
}

void matchProcess(Match& match) {
    cameraProcess(match.camera, match.player);
    playerProcess(match.player);
}

void cameraProcess(Camera2D& camera, Player& player) {

}

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.pos.x -= 4;
}