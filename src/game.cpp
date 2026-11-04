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
            // declareButtons();   //Nao sei se fica aqui ou se coloco quando abre o jogo
                                //Pois nao sei se e bom recarregar os botoes toda vez que o cara vai pro menu
                                //Talvez seja melhor declarar sempre no comeco da partida
                                //Que que tu acha?
            matchProcess(game.current_match);
        break;

    }
}

void gameOver(Game& game){
    return;
}