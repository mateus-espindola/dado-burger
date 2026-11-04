#include "../include/game.hpp"

void gameStart(Game& game){
    loadSpritesheet(game.sprites);

    game.current_match.player.object.sprite = game.sprites[SPR_PLAYER];
    game.current_match.player.object.radius = PLAYER_HITBOX_RADIUS;

    // AJEITAR DESPUES
    matchStart(game.current_match);

    game.state = PLAYING;
    game.quit = false;
}

void loadSpritesheet(Sprite sprites[]) {
    // Array apenas com os caminhos, na mesma ordem dos enums (0, 1, ...)
    const char *paths[QUANTITY_OF_SPRITES] = {
        [SPR_BACKGROUND] = "assets/sprites/background.png",
        [SPR_PLAYER]     = "assets/sprites/player.png"
    };

    for (int i = 0; i < QUANTITY_OF_SPRITES; i++) {
        sprites[i].texture = LoadTexture(paths[i]);
        sprites[i].width   = sprites[i].texture.width;
        sprites[i].height  = sprites[i].texture.height;
    }
}

void unloadSpritesheet(Sprite sprites[]) {
    for (int i = 0; i < QUANTITY_OF_SPRITES; i++) {
        UnloadTexture(sprites[i].texture);
    }
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
    unloadSpritesheet(game.sprites);
}

void matchStart(Match& match) {
    match.player.object.pos = PLAYER_START_POS;

    match.camera = { 0 };

    match.camera.target = { match.player.object.pos.x, match.player.object.pos.y};
    match.camera.offset = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - PLAYER_START_POS.y / 2.0f };
    match.camera.zoom = 1.0f;
}

void matchProcess(Match& match) {
    cameraProcess(match.camera, match.player);
    playerProcess(match.player);
}

void cameraProcess(Camera2D& camera, Player& player) {
    Vector2 targetPos = { player.object.pos.x, player.object.pos.y};

    camera.target.x += (targetPos.x - camera.target.x) * CAMERA_INTERPOOLATION;
    std::cout << "Camera target: (" << camera.target.x << ", " << camera.target.y << ")" << std::endl;
}

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.object.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.object.pos.x -= 4;
}