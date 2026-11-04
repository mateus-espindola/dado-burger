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
            matchProcess(game.current_match, game.sprites[SPR_BACKGROUND]);
        break;

    }
}

void gameOver(Game& game){
    unloadSpritesheet(game.sprites);
}

void matchStart(Match& match) {
    match.player.object.pos = PLAYER_START_POS;
    match.player.direction = DIR_RIGHT;

    match.camera = { 0 };

    match.camera.target = { match.player.object.pos.x, match.player.object.pos.y};
    match.camera.offset = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - PLAYER_START_POS.y / 2.0f };
    match.camera.zoom = 1.0f;
}

void matchProcess(Match& match, Sprite background) {
    cameraProcess(match.camera, match.player, background);
    playerProcess(match.player, background);
}

void cameraProcess(Camera2D& camera, Player& player, Sprite background) {
    Vector2 targetPos = { player.object.pos.x, player.object.pos.y};

    camera.target.x += (targetPos.x - camera.target.x) * CAMERA_INTERPOOLATION;

    if (camera.target.x < camera.offset.x) {
        camera.target.x = camera.offset.x;
    }
    if (camera.target.x > background.width * GAME_SCALE - camera.offset.x) {
        camera.target.x = background.width * GAME_SCALE - camera.offset.x;
    }
}

void playerProcess(Player& player, Sprite background) {
    int playerSpeed;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        playerSpeed = PLAYER_SPEED * 2;
    } else {
        playerSpeed = PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player.direction = DIR_RIGHT;
        player.object.pos.x += playerSpeed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player.direction = DIR_LEFT;
        player.object.pos.x -= playerSpeed;
    }

    float minX = 0.0f + (player.object.sprite.width * GAME_SCALE) / 2;
    float maxX = background.width * GAME_SCALE - (player.object.sprite.width * GAME_SCALE) / 2;

    if (player.object.pos.x < minX) player.object.pos.x = minX;
    if (player.object.pos.x > maxX) player.object.pos.x = maxX;
}