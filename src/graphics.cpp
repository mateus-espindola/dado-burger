#include <cstdio>
#include <cstring>
#include <cmath>

#include "../include/graphics.hpp"
#include "../include/camera.hpp"
#include "../include/button_constants.hpp"
#include "../include/graphic_constants.hpp"
#include "../include/inputs.hpp"
#include "raylib.h"


// Setado uma vez em gameStart (match.spriteMatch[SPR_MENU_BACKGROUND]). drawMenu/drawPause/
// drawVictory/drawDefeat nao recebem Sprite/Match sempre, entao usam esse global pra desenhar
// o fundo. Sem ele (chamada antes do load) so fica o RAYWHITE do ClearBackground.
static Sprite* g_menuBackground = nullptr;

void setMenuBackground(Sprite& bg) {
    g_menuBackground = &bg;
}

static Rectangle growRect(Rectangle r, float pad) {
    return { r.x - pad, r.y - pad, r.width + 2 * pad, r.height + 2 * pad };
}

static Rectangle rectUnion(Rectangle a, Rectangle b) {
    float x1 = fminf(a.x, b.x), y1 = fminf(a.y, b.y);
    float x2 = fmaxf(a.x + a.width, b.x + b.width), y2 = fmaxf(a.y + a.height, b.y + b.height);
    return { x1, y1, x2 - x1, y2 - y1 };
}

static Rectangle textRect(const char* text, int fs, float x, float y) {
    return { x, y, (float)MeasureText(text, fs), (float)fs };
}

// Uniao das shapes de todos os botoes do vetor (usado pra encaixar a caixa de fundo so
// na area onde ha conteudo, sem cobrir a tela inteira). Vazio = retangulo degenerado.
static Rectangle buttonsBBox(const ButtonVec& buttons) {
    if (buttons.size == 0) return { 0, 0, 0, 0 };

    Rectangle box = buttons.buttons[0].shape;
    for (int i = 1; i < buttons.size; i++) box = rectUnion(box, buttons.buttons[i].shape);
    return box;
}

// Mesma ideia, mas so pra um intervalo [start, start+count) do array (grupos dentro de uma tela)
static Rectangle buttonsBBoxRange(const Button* buttons, int start, int count) {
    Rectangle box = buttons[start].shape;
    for (int i = 1; i < count; i++) box = rectUnion(box, buttons[start + i].shape);
    return box;
}

// Painel decorativo (fundo + borda) atras de um grupo de botoes, estilo drawStove
static void drawPanel(Rectangle box, float pad, Color fill, Color border, float borderThick) {
    Rectangle r = growRect(box, pad);
    DrawRectangleRec(r, fill);
    DrawRectangleLinesEx(r, borderThick, border);
}

// Fundo (se setado) + caixa preta translucida atras do conteudo (`contentBox` ja deve
// incluir toda a area de texto/botoes relevante). Chamar logo depois do ClearBackground,
// antes de qualquer texto/botao do menu.
static void drawMenuBackdrop(Rectangle contentBox) {
    if (g_menuBackground != nullptr) {
        DrawTexturePro(
            g_menuBackground->texture,
            (Rectangle){0, 0, (float)g_menuBackground->width, (float)g_menuBackground->height},
            (Rectangle){0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT},
            (Vector2){0, 0},
            0.0f,
            WHITE
        );
    }

    DrawRectangleRec(growRect(contentBox, MENU_OVERLAY_PADDING), Fade(BLACK, MENU_OVERLAY_OPACITY));
}

void drawMenu(const ButtonVec& menuButtons, int butUnderMouseInd){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "DADO BURGER";
        int titleFs = 60;
        int titleX = WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, titleY = 150;

        drawMenuBackdrop(rectUnion(textRect(title, titleFs, titleX, titleY), buttonsBBox(menuButtons)));

        DrawText(title, titleX, titleY, titleFs, BEIGE);

        for (int i = 0; i < menuButtons.size; i++) {
            const Button &b = menuButtons.buttons[i];

            Color fill = (i == butUnderMouseInd) ? ORANGE : BEIGE;
            DrawRectangleRec(b.shape, fill);
            DrawRectangleLinesEx(b.shape, 3, DARKBROWN);

            int fs = 28;
            int textW = MeasureText(b.text, fs);
            DrawText(b.text, (int)(b.shape.x + b.shape.width / 2 - textW / 2),
                     (int)(b.shape.y + b.shape.height / 2 - fs / 2), fs, DARKBROWN);
        }

    EndDrawing();
}

void drawPause(Match& match, int butUnderMouseInd){
    const ButtonVec& pauseButtons = match.buttonsVec[PAUSED];

    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "PAUSED";
        int titleFs = 60;
        int titleX = WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, titleY = 150;

        drawMenuBackdrop(rectUnion(textRect(title, titleFs, titleX, titleY), buttonsBBox(pauseButtons)));

        DrawText(title, titleX, titleY, titleFs, BEIGE);

        for (int i = 0; i < pauseButtons.size; i++) {
            const Button &b = pauseButtons.buttons[i];

            Color fill = (i == butUnderMouseInd) ? ORANGE : BEIGE;
            DrawRectangleRec(b.shape, fill);
            DrawRectangleLinesEx(b.shape, 3, DARKBROWN);

            int fs = 28;
            int textW = MeasureText(b.text, fs);
            DrawText(b.text, (int)(b.shape.x + b.shape.width / 2 - textW / 2),
                     (int)(b.shape.y + b.shape.height / 2 - fs / 2), fs, DARKBROWN);
        }

    EndDrawing();
}

// Inspirado na desenhaTextoVitoria do TrabalhoFinalAlgProg: nome digitado em tempo real
// com cursor piscando (pisca via GetTime(), nao precisa guardar contador em lugar nenhum)
void drawVictory(Match& match, int butUnderMouseInd){
    (void)butUnderMouseInd; // tela nao tem botoes, so o campo de nome

    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "VOCE VENCEU!";
        int titleFs = 60;
        int titleX = WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, titleY = 120;

        const char* moneyTxt = TextFormat("Dinheiro ganho: $ %d", match.player.money);
        int moneyFs = 28;
        int moneyX = WINDOW_WIDTH / 2 - MeasureText(moneyTxt, moneyFs) / 2, moneyY = 220;

        const char* prompt = "Digite seu nome:";
        int promptFs = 26;
        int promptX = WINDOW_WIDTH / 2 - MeasureText(prompt, promptFs) / 2, promptY = 300;

        Rectangle inputBox = { WINDOW_WIDTH / 2.0f - 220, 350, 440, 50 };

        const char* hint = "Pressione ENTER para salvar";
        int hintFs = 20;
        int hintX = WINDOW_WIDTH / 2 - MeasureText(hint, hintFs) / 2, hintY = (int)(inputBox.y + inputBox.height + 20);

        Rectangle box = textRect(title, titleFs, titleX, titleY);
        box = rectUnion(box, textRect(moneyTxt, moneyFs, moneyX, moneyY));
        box = rectUnion(box, textRect(prompt, promptFs, promptX, promptY));
        box = rectUnion(box, inputBox);
        box = rectUnion(box, textRect(hint, hintFs, hintX, hintY));
        drawMenuBackdrop(box);

        DrawText(title, titleX, titleY, titleFs, GREEN);
        DrawText(moneyTxt, moneyX, moneyY, moneyFs, DARKGREEN);
        DrawText(prompt, promptX, promptY, promptFs, DARKBROWN);

        DrawRectangleRec(inputBox, RAYWHITE);
        DrawRectangleLinesEx(inputBox, 2, DARKBROWN);

        int textFs = 26;
        DrawText(match.nameInput, (int)(inputBox.x + 10), (int)(inputBox.y + inputBox.height / 2 - textFs / 2), textFs, BLACK);

        // cursor piscando: liga/desliga 2x por segundo
        if (fmodf(GetTime(), 1.0f) < 0.5f) {
            int cursorX = (int)(inputBox.x + 10 + MeasureText(match.nameInput, textFs) + 2);
            DrawText("|", cursorX, (int)(inputBox.y + inputBox.height / 2 - textFs / 2), textFs, BLACK);
        }

        DrawText(hint, hintX, hintY, hintFs, GRAY);

    EndDrawing();
}

void drawDefeat(Match& match, int butUnderMouseInd){
    (void)match;
    (void)butUnderMouseInd;

    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "VOCE PERDEU!";
        int titleFs = 60;
        int titleX = WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, titleY = WINDOW_HEIGHT / 2 - titleFs;

        const char* hint = "Pressione ENTER para voltar ao menu";
        int hintFs = 24;
        int hintX = WINDOW_WIDTH / 2 - MeasureText(hint, hintFs) / 2, hintY = WINDOW_HEIGHT / 2 + 20;

        drawMenuBackdrop(rectUnion(textRect(title, titleFs, titleX, titleY), textRect(hint, hintFs, hintX, hintY)));

        DrawText(title, titleX, titleY, titleFs, RED);
        DrawText(hint, hintX, hintY, hintFs, GRAY);

    EndDrawing();
}

// Setado uma vez em gameStart (match.spriteMatch[SPR_HOW_TO_PLAY])
static Sprite* g_howToPlayImg = nullptr;

void setHowToPlayImage(Sprite& img) {
    g_howToPlayImg = &img;
}

void drawHowToPlay(){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "HOW TO PLAY";
        int titleFs = 50;
        int titleX = WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, titleY = 60;

        const char* hint = "Pressione ENTER para voltar ao menu";
        int hintFs = 22;
        int hintX = WINDOW_WIDTH / 2 - MeasureText(hint, hintFs) / 2, hintY = WINDOW_HEIGHT - 80;

        drawMenuBackdrop(rectUnion(textRect(title, titleFs, titleX, titleY), textRect(hint, hintFs, hintX, hintY)));

        if (g_howToPlayImg != nullptr) {
            Rectangle dest = { WINDOW_WIDTH / 2.0f - HOW_TO_PLAY_IMG_W / 2.0f, WINDOW_HEIGHT / 2.0f - HOW_TO_PLAY_IMG_H / 2.0f,
                                HOW_TO_PLAY_IMG_W, HOW_TO_PLAY_IMG_H };
            DrawTexturePro(
                g_howToPlayImg->texture,
                (Rectangle){0, 0, (float)g_howToPlayImg->width, (float)g_howToPlayImg->height},
                dest,
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
        }

        DrawText(title, titleX, titleY, titleFs, BEIGE);
        DrawText(hint, hintX, hintY, hintFs, GRAY);

    EndDrawing();
}

void drawHistory(const ContiguousList<PlayerInfo>& historico, int page, const ButtonVec& historyButtons, int butUnderMouseInd){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "HISTORY";
        int titleFs = 50;
        int titleX = WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, titleY = 60;

        int totalPages = (historico.size + HISTORY_ENTRIES_PER_PAGE - 1) / HISTORY_ENTRIES_PER_PAGE;
        if (totalPages < 1) totalPages = 1;

        int start = page * HISTORY_ENTRIES_PER_PAGE;
        int end   = start + HISTORY_ENTRIES_PER_PAGE;
        if (end > historico.size) end = historico.size;

        // snprintf em buffer proprio, nao TextFormat: o loop abaixo chama TextFormat("%d", score)
        // por entrada, e o buffer circular interno do raylib (poucos slots) acaba reciclando e
        // corrompendo pageTxt antes dele ser desenhado la na frente.
        char pageTxtBuf[32];
        snprintf(pageTxtBuf, sizeof(pageTxtBuf), "Page %d / %d", page + 1, totalPages);
        const char* pageTxt = pageTxtBuf;
        int pageX = WINDOW_WIDTH / 2 - MeasureText(pageTxt, 24) / 2, pageY = HISTORY_NAV_BUTTON_Y - 40;

        Rectangle box = textRect(title, titleFs, titleX, titleY);
        box = rectUnion(box, textRect(pageTxt, 24, pageX, pageY));
        box = rectUnion(box, buttonsBBox(historyButtons));
        if (end > start) {
            Rectangle listArea = { (float)HISTORY_LIST_LEFT_X, (float)HISTORY_LIST_TOP_Y,
                                    (float)(HISTORY_LIST_NAME_W + 100), (float)((end - start) * HISTORY_LIST_ROW_H) };
            box = rectUnion(box, listArea);
        }
        drawMenuBackdrop(box);

        DrawText(title, titleX, titleY, titleFs, BEIGE);

        int y = HISTORY_LIST_TOP_Y;
        for (int i = start; i < end; i++) {
            const PlayerInfo &info = historico.data[i];
            DrawText(info.nome.c_str(), HISTORY_LIST_LEFT_X, y, 24, RAYWHITE);
            DrawText(TextFormat("%d", info.score), HISTORY_LIST_LEFT_X + HISTORY_LIST_NAME_W, y, 24, RAYWHITE);
            y += HISTORY_LIST_ROW_H;
        }

        DrawText(pageTxt, pageX, pageY, 24, RAYWHITE);

        for (int i = 0; i < historyButtons.size; i++) {
            const Button &b = historyButtons.buttons[i];

            bool atFirst = page == 0;
            bool atLast  = page == totalPages - 1;
            bool disabled = ((strcmp(b.text, "PREV") == 0 || strcmp(b.text, "<<") == 0) && atFirst)
                          || ((strcmp(b.text, "NEXT") == 0 || strcmp(b.text, ">>") == 0) && atLast);

            Color fill = disabled ? LIGHTGRAY : ((i == butUnderMouseInd) ? ORANGE : BEIGE);
            DrawRectangleRec(b.shape, fill);
            DrawRectangleLinesEx(b.shape, 3, DARKBROWN);

            int fs = 22;
            int textW = MeasureText(b.text, fs);
            DrawText(b.text, (int)(b.shape.x + b.shape.width / 2 - textW / 2),
                     (int)(b.shape.y + b.shape.height / 2 - fs / 2), fs, DARKBROWN);
        }

    EndDrawing();
}

// Simula a quina da geladeira: linha solida por cima de tudo, na divisa kitchen/fridge
void drawFridgeWall() {
    DrawRectangle((int)FRIDGE_WALL_X, (int)FRIDGE_WALL_Y, (int)FRIDGE_WALL_W, (int)FRIDGE_WALL_H, DARKGRAY);
}

void drawKitchen(Match& match, int butUnderMouseInd){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const ButtonVec &buttonsVec = match.buttonsVec[match.screen];

        BeginMode2D(match.camera);
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), match.camera);

            spriteDraw(match.spriteMatch[SPR_KITCHEN_BACKGROUND], (Vector2){0, 0}, WINDOW_HEIGHT, WHITE);

            drawCostumers(match.costumer_line, match.costumer_counter);

            spriteDraw(match.spriteMatch[SPR_KITCHEN], (Vector2){0, 0}, WINDOW_HEIGHT, WHITE);

            int visible = -1;   //Index of the visible button in drawNearesBut

            if(match.screen == FRIDGE){
                drawButtons(buttonsVec, butUnderMouseInd, match.screen);
            }
            else{
                visible = drawNearestBut(match.player, buttonsVec);
                drawButGlow(buttonsVec.buttons[visible].shape, WHITE, BRIGHTNESS_LAYERS, BRIGHTNESS);
            }


            playerDraw(match.player);

            if(DRAW_HITBOX == 1) hitboxDraw(match.player.object);

            drawCostumerOrders(match.costumer_counter, mouseWorld);

            drawFridgeWall();

        EndMode2D();

        drawHUD(match.player, match.costumer_line.costumers_generated >= COSTUMERS_PER_MATCH, match.costumer_line.costumers_that_left);

    EndDrawing();
}

// Setado uma vez em loadSpritesheet (match.spriteMatch[SPR_INGREDIENTS]). drawIngredient
// usa o atlas se disponivel; sem ele (chamada antes do load, ou tipo fora do atlas) cai no circulo.
static Sprite* g_ingredientAtlas = nullptr;

void setIngredientAtlas(Sprite& atlas) {
    g_ingredientAtlas = &atlas;
}

static int ingredientAtlasRow(IngredientType t); // definido mais abaixo, junto do resto do atlas

// Indices dos botoes de prepare (definidos em buttons.cpp:declareButtons)
#define PREPARE_SALAD_START   0
#define PREPARE_SALAD_COUNT   5
#define PREPARE_BOTTLE_START  5
#define PREPARE_BOTTLE_COUNT  3
#define PREPARE_PROTEIN_START 8
#define PREPARE_PROTEIN_COUNT 5
#define PREPARE_BREAD_START   13
#define PREPARE_BREAD_COUNT   2
#define PREPARE_BURGER_START  15
#define PREPARE_BURGER_COUNT  3

// Desenha a celula [row][col] do atlas de ingredientes direto por tipo (sem depender de um
// Ingredient/estado de cozimento) - usado pros botoes de garrafa, que so tem um desenho fixo.
static void drawIngredientAtlasCell(Sprite& atlas, Vector2 center, float size, IngredientType type, int col) {
    int row = ingredientAtlasRow(type);
    if (row < 0) return;

    Rectangle src = {
        (float)(col * INGREDIENT_ATLAS_CELL),
        (float)(row * INGREDIENT_ATLAS_CELL),
        (float)INGREDIENT_ATLAS_CELL,
        (float)INGREDIENT_ATLAS_CELL
    };
    Rectangle dest = { center.x - size / 2, center.y - size / 2, size, size };

    DrawTexturePro(atlas.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
}

void drawPrepare(Match &match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    const ButtonVec &buttonsVec = match.buttonsVec[match.screen];
    const Button* buttons = buttonsVec.buttons;

    // salada e paes: um quadrado cinza individual por botao (nao um painel agrupado)
    for (int i = 0; i < PREPARE_SALAD_COUNT; i++) drawPanel(buttons[PREPARE_SALAD_START + i].shape, 10.0f, GRAY, LIGHTGRAY, 3);
    for (int i = 0; i < PREPARE_BREAD_COUNT; i++)  drawPanel(buttons[PREPARE_BREAD_START + i].shape, 10.0f, GRAY, LIGHTGRAY, 3);

    // burger: um unico retangulo maroon cobrindo as 3 stacks do meio
    drawPanel(buttonsBBoxRange(buttons, PREPARE_BURGER_START, PREPARE_BURGER_COUNT), 20.0f, MAROON, DARKBROWN, 4);

    // proteina: um unico retangulo cinza escuro cobrindo os 5 heaps
    drawPanel(buttonsBBoxRange(buttons, PREPARE_PROTEIN_START, PREPARE_PROTEIN_COUNT), 20.0f, DARKGRAY, GRAY, 4);

    // garrafas: ketchup/mustard/pickles desenhados como o ingrediente em si (coluna 0 do atlas,
    // linha de cada um), concentrico com o botao e na mesma altura dele
    if (g_ingredientAtlas != nullptr) {
        static const IngredientType bottleTypes[PREPARE_BOTTLE_COUNT] = { KETCHUP, MUSTARD, PICKLES };
        for (int i = 0; i < PREPARE_BOTTLE_COUNT; i++) {
            Rectangle shape = buttons[PREPARE_BOTTLE_START + i].shape;
            Vector2 center = { shape.x + shape.width / 2, shape.y + shape.height / 2 };
            drawIngredientAtlasCell(*g_ingredientAtlas, center, shape.height, bottleTypes[i], 0);
        }
    }

    drawButtons(buttonsVec, butUnderMouseInd, match.screen);

    drawHUD(match.player, match.costumer_line.costumers_generated >= COSTUMERS_PER_MATCH, match.costumer_line.costumers_that_left);

    EndDrawing();
}

#define BOARD_STACKS_START  0
#define BOARD_STACKS_COUNT  5  // 3 STACK esquerda + 2 STACK direita
#define BOARD_READIES_INDEX 5  // READIES_STACK

void drawBoard(Match match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        // chão e paredes
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, LIGHTGRAY);
        DrawRectangleLinesEx((Rectangle){ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }, 12, DARKGRAY);

        const ButtonVec &buttonsVec = match.buttonsVec[match.screen];

        // painel amadeirado cobrindo as 5 stacks de ingrediente (nao inclui readies nem a tabua)
        const float panelPad = 20.0f;
        Color woodFill = { 181, 136, 99, 255 };
        Color woodBorder = DARKBROWN;
        drawPanel(buttonsBBoxRange(buttonsVec.buttons, BOARD_STACKS_START, BOARD_STACKS_COUNT), panelPad, woodFill, woodBorder, 4);

        // readies: quadrado maroon com circulo verde-escuro dentro, concentrico e maior que a stack
        {
            Rectangle readiesShape = buttonsVec.buttons[BOARD_READIES_INDEX].shape;
            Vector2 center = { readiesShape.x + readiesShape.width / 2, readiesShape.y + readiesShape.height / 2 };
            Rectangle readiesSquare = growRect(readiesShape, panelPad);
            DrawRectangleRec(readiesSquare, MAROON);
            DrawCircleV(center, readiesSquare.width / 2, DARKGREEN);
        }

        // tábua de corte em si (o retangulo verde generico do botao INSERT dela e pulado em drawButtons)
        Rectangle board = { BOARD_X, BOARD_Y, BOARD_W, BOARD_H };
        DrawRectangleRec(board, (Color){ 139, 90, 43, 255 });
        DrawRectangleLinesEx(board, 4, DARKBROWN);

        drawButtons(buttonsVec, butUnderMouseInd, match.screen);

        drawHUD(match.player, match.costumer_line.costumers_generated >= COSTUMERS_PER_MATCH, match.costumer_line.costumers_that_left);

    EndDrawing();
}




// Grade de círculos pretos, centrados em cada célula da área
static void drawCircleGrid(Rectangle area, int cols, int rows, float radius) {
    float cw = area.width  / cols;
    float ch = area.height / rows;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            DrawCircleV({ area.x + (c + 0.5f) * cw, area.y + (r + 0.5f) * ch }, radius, BLACK);
}

// Grade de quadrados pretos, centrados em cada célula da área
static void drawSquareGrid(Rectangle area, int cols, int rows, float side) {
    float cw = area.width  / cols;
    float ch = area.height / rows;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            Rectangle sq = { area.x + (c + 0.5f) * cw - side / 2,
                             area.y + (r + 0.5f) * ch - side / 2, side, side };
            DrawRectangleRec(sq, BLACK);
        }
}

#define OVEN_READIES_INDEX (OVEN_BUTTON_COUNT * 3) // 3 grupos de OVEN_BUTTON_COUNT antes do READY

void drawStove(Match& match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        BeginMode2D(match.camera);

            const ButtonVec &buttonsVec = match.buttonsVec[match.screen];

            // corpo do fogão (cobre o mundo todo)
            DrawRectangle(0, 0, STOVE_WORLD_WIDTH, STOVE_WORLD_HEIGHT, LIGHTGRAY);

            // 2) espaço do meio: 2 colunas x 3 quadrados
            Rectangle squares = { SQUARES_X, PANEL_Y, SQUARES_W, PANEL_H };
            DrawRectangleRec(squares, GRAY);
            DrawRectangleLinesEx(squares, 6, DARKGRAY);
            drawSquareGrid(squares, 1, 3, 140);

            // 1) chapa à esquerda: 6 círculos (2 colunas x 3 linhas)
            Rectangle plate = { PLATE_X, PANEL_Y, PLATE_W, PANEL_H };
            DrawRectangleRec(plate, DARKGRAY);
            DrawRectangleLinesEx(plate, 6, GRAY);
            drawCircleGrid(plate, 2, 3, 80);

            // 3) seção da direita: 1 coluna x 3 círculos
            Rectangle readies = { READIES_X, READIES_Y, READIES_W, READIES_H };
            DrawRectangleRec(readies, GRAY);
            DrawRectangleLinesEx(readies, 6, DARKGRAY);
            drawSquareGrid(readies, 1, 2, 140);

            // readies stack (READIES_HEAP): quadrado maroon com circulo verde-escuro dentro,
            // concentrico e maior que o botao - mesma decoracao do readies da tabua de corte
            {
                Rectangle readiesShape = buttonsVec.buttons[OVEN_READIES_INDEX].shape;
                Vector2 center = { readiesShape.x + readiesShape.width / 2, readiesShape.y + readiesShape.height / 2 };
                Rectangle readiesSquare = growRect(readiesShape, 20.0f);
                DrawRectangleRec(readiesSquare, MAROON);
                DrawCircleV(center, readiesSquare.width / 2, DARKGREEN);
            }

            drawButtons(buttonsVec, butUnderMouseInd, match.screen);

        EndMode2D();

        drawHUD(match.player, match.costumer_line.costumers_generated >= COSTUMERS_PER_MATCH, match.costumer_line.costumers_that_left);

    EndDrawing();
}


// Cor do círculo de cada ingrediente
static Color ingredientColor(IngredientType t) {
    switch (t) {
        case LETTUCE:       return GREEN;
        case TOMATO:        return RED;
        case BACON:         return PINK;
        case ONION:         return PURPLE;
        case KETCHUP:       return MAROON;
        case MUSTARD:       return YELLOW;
        case MEAT:          return BROWN;
        case EGG:           return RAYWHITE;
        case PICKLES:       return LIME;
        case CHEDDAR:       return ORANGE;
        case SWISS_CHEESE:  return GOLD;
        case UPPER_BREAD:   return BEIGE;
        case LOWER_BREAD:   return BEIGE;
        default:            return BLANK;   // NONE ou ingrediente sem cor definida
    }
}

// Linha do ingrediente no atlas (assets/sprites/ingredients.png, grid 24x24).
// -1 = tipo sem sprite no atlas (NONE, BURGER).
static int ingredientAtlasRow(IngredientType t) {
    switch (t) {
        case LETTUCE:       return 0;
        case BACON:         return 1;
        case ONION:         return 2;
        case KETCHUP:       return 3;
        case MUSTARD:       return 4;
        case MEAT:          return 5;
        case EGG:           return 6;
        case PICKLES:       return 7;
        case CHEDDAR:       return 8;
        case SWISS_CHEESE:  return 9;
        case TOMATO:        return 10;
        case UPPER_BREAD:   return 11;
        case LOWER_BREAD:   return 12;
        default:            return -1;
    }
}

// Coluna do CookPoint no atlas: NEEDS_TO_CUT=-2 ... OVER_COOKED=4, desloca pra 0..6
static int ingredientAtlasCol(CookPoint p) {
    return p - NEEDS_TO_CUT;
}

// Desenha a celula do atlas correspondente ao tipo/estado do ingrediente, centrada em `center`.
// practicalCookingStateOf decide o estado quando os dois lados divergem (ex. ingrediente flipavel).
void drawIngredientSprite(Sprite& atlas, Vector2 center, float size, const Ingredient& ing) {
    int row = ingredientAtlasRow(ing.type);
    if (row < 0) return;

    int col = ingredientAtlasCol(practicalCookingStateOf(ing));

    Rectangle src = {
        (float)(col * INGREDIENT_ATLAS_CELL),
        (float)(row * INGREDIENT_ATLAS_CELL),
        (float)INGREDIENT_ATLAS_CELL,
        (float)INGREDIENT_ATLAS_CELL
    };
    Rectangle dest = { center.x - size / 2, center.y - size / 2, size, size };

    DrawTexturePro(atlas.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
}

// Nome legivel do ingrediente
static const char* ingredientName(IngredientType t) {
    switch (t) {
        case LETTUCE:       return "Lettuce";
        case TOMATO:        return "Tomato";
        case BACON:         return "Bacon";
        case ONION:         return "Onion";
        case KETCHUP:       return "Ketchup";
        case MUSTARD:       return "Mustard";
        case MEAT:          return "Meat";
        case EGG:           return "Egg";
        case PICKLES:       return "Pickles";
        case CHEDDAR:       return "Cheddar";
        case SWISS_CHEESE:  return "Swiss Cheese";
        case UPPER_BREAD:   return "Upper Bread";
        case LOWER_BREAD:   return "Lower Bread";
        default:            return "?";
    }
}

void drawInventory(const Player &player) {
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        const Stack &slot = player.inventory[i];

        Rectangle r = { INV_X + i * (INV_SLOT_SIZE + INV_SLOT_GAP), INV_Y,
                        INV_SLOT_SIZE, INV_SLOT_SIZE };

        // fundo meio transparente (todos os slots)
        DrawRectangleRec(r, Fade(BLACK, 0.4f));

        // destaque do slot selecionado
        if (i == player.selectedSlot)
            DrawRectangleLinesEx(r, 3, WHITE);
        else
            DrawRectangleLinesEx(r, 1, Fade(WHITE, 0.4f));

        // item, se houver
        if (slot.size > 0 && slot.type != NONE) {
            Vector2 center = { r.x + r.width / 2, r.y + r.height / 2 };

            if (slot.type == BURGER) {
                // desenha as camadas reais do hamburguer, de baixo para cima
                Vector2 base = { center.x, r.y + r.height - INV_SLOT_SIZE * 0.3f };
                drawStack(slot, base, INV_SLOT_SIZE * 0.22f, INV_SLOT_SIZE * 0.08f);
            } else {
                drawIngredient(center, INV_SLOT_SIZE * 0.3f, slot.top->data);
            }

            // quantidade no canto inferior direito
            if (slot.size > 1 && slot.type != BURGER)
                DrawText(TextFormat("%d", slot.size),
                         (int)(r.x + r.width - 22), (int)(r.y + r.height - 22), 20, WHITE);
        }
    }
}

#define MONEY_RECT_W 160
#define MONEY_RECT_H 50
#define MONEY_MARGIN 20

// Dinheiro do player, no canto superior direito
void drawMoney(const Player &player) {
    Rectangle r = { WINDOW_WIDTH - MONEY_RECT_W - MONEY_MARGIN, MONEY_MARGIN, MONEY_RECT_W, MONEY_RECT_H };

    DrawRectangleRounded(r, 0.3f, 8, Fade(DARKGREEN, 0.5f));
    DrawRectangleRoundedLines(r, 0.3f, 8, 2, GREEN);

    const char* text = TextFormat("$ %d", player.money);
    const int fs = 24;
    int tw = MeasureText(text, fs);
    DrawText(text, (int)(r.x + r.width / 2 - tw / 2), (int)(r.y + r.height / 2 - fs / 2), fs, GREEN);
}

// Avisa que ja deu pra encerrar a partida (sem mais clientes pra gerar), desenhado do
// lado do inventario
void drawFinishMatchHint() {
    const char* text = "Press F to finish the match";
    const int fs = 20;

    DrawText(text, (int)INV_X, (int)(INV_Y + INV_SLOT_SIZE + 10), fs, YELLOW);
}

#define LEFT_X_SIZE 20
#define LEFT_X_GAP  10
#define LEFT_X_Y    20
#define LEFT_X_THICK 4

// Um X vermelho no topo-meio da tela pra cada cliente que desistiu (costumers_that_left),
// limitado a COSTUMERS_PER_MATCH - COSTUMER_LEAVE_TOLERANCE (a margem antes de perder a partida)
void drawCostumersLeftX(int costumersThatLeft) {
    int maxX = COSTUMERS_PER_MATCH - COSTUMER_LEAVE_TOLERANCE;
    if (maxX <= 0) return;

    int count = (costumersThatLeft < maxX) ? costumersThatLeft : maxX;

    int totalWidth = maxX * LEFT_X_SIZE + (maxX - 1) * LEFT_X_GAP;
    int startX = WINDOW_WIDTH / 2 - totalWidth / 2;

    for (int i = 0; i < count; i++) {
        float x = (float)(startX + i * (LEFT_X_SIZE + LEFT_X_GAP));
        float y = (float)LEFT_X_Y;

        DrawLineEx({ x, y }, { x + LEFT_X_SIZE, y + LEFT_X_SIZE }, LEFT_X_THICK, RED);
        DrawLineEx({ x + LEFT_X_SIZE, y }, { x, y + LEFT_X_SIZE }, LEFT_X_THICK, RED);
    }
}

// Tudo que fica sempre na tela durante a partida
void drawHUD(const Player &player, bool showFinishHint, int costumersThatLeft) {
    drawInventory(player);
    drawMoney(player);
    drawCostumersLeftX(costumersThatLeft);

    if (showFinishHint) drawFinishMatchHint();
}

// Desenha um ingrediente (sprite do atlas se disponivel, senao circulo + contorno;
// sempre com texto pequeno do ponto de preparo acima, se houver)
void drawIngredient(Vector2 center, float radius, const Ingredient& ing) {
    bool drewSprite = false;

    if (g_ingredientAtlas != nullptr && ingredientAtlasRow(ing.type) >= 0) {
        drawIngredientSprite(*g_ingredientAtlas, center, radius * 2.0f, ing);
        drewSprite = true;
    }

    if (!drewSprite) {
        Color color = ingredientColor(ing.type);
        if (ing.cook_state.cookInfo[0].cookPoint == OVER_COOKED || ing.cook_state.cookInfo[1].cookPoint == OVER_COOKED) {
            color = BLACK;
        }
        DrawCircleV(center, radius, color);
        DrawCircleLines(center.x, center.y, radius, BLACK);
    }
}

// Desenha os nós da pilha a partir do fundo (recursão desce até o fundo e desenha ao voltar)
static int drawStackRec(Stack_node* node, Vector2 basePos, float radius, float offset) {
    if (node == nullptr) return 0;

    int depthBelow = drawStackRec(node->below, basePos, radius, offset);

    Vector2 center = { basePos.x, basePos.y - depthBelow * offset };
    drawIngredient(center, radius, node->data);

    return depthBelow + 1;
}

void drawStack(const Stack& stack, Vector2 basePos, float radius, float offset) {
    drawStackRec(stack.top, basePos, radius, offset);
}

// Barra vertical de decaimento do ingrediente mais perto de estragar (raiz do heap),
// desenhada do lado do heap quando o mouse esta por cima. perish_time == -1 nunca estraga.
static void drawHeapRotBar(const Ingredient& closest, Vector2 basePos, float radius) {
    float maxPerish = (float) perishTimeOf(closest.type);
    if (maxPerish <= 0) return; // nao estraga, nada a mostrar

    float frac = closest.perish_time / maxPerish;
    if (frac < 0) frac = 0;
    if (frac > 1) frac = 1;

    Color color = (frac >= 0.5f) ? GREEN : (frac >= 0.2f) ? YELLOW : RED;

    float barH = radius * 2;
    Rectangle bg   = { basePos.x + radius + ROT_BAR_GAP, basePos.y - radius, ROT_BAR_W, barH };
    Rectangle fill = { bg.x, bg.y + bg.height * (1.0f - frac), bg.width, bg.height * frac };

    DrawRectangleRec(bg, Fade(BLACK, 0.4f));
    DrawRectangleRec(fill, color);
    DrawRectangleLinesEx(bg, 1.0f, BLACK);
}

// Desenha o heap como uma pilha visual: a raiz (mais perto de estragar) fica no topo,
// os demais ficam abaixo em qualquer ordem (o heap nao tem ordem total alem da raiz).
void drawHeap(const Heap<Ingredient>& heap, Vector2 basePos, float radius, float offset, bool hovered) {
    for (int i = heap.size - 1; i >= 0; i--) {
        float depthFromBottom = (float)((heap.size - 1) - i);
        Vector2 center = { basePos.x, basePos.y - depthFromBottom * offset };
        drawIngredient(center, radius, heap.data[i]);
    }

    if (hovered && heap.size > 0) {
        // raiz (data[0]) e o mais perto de estragar e e desenhado no topo da pilha visual,
        // ou seja na maior profundidade (heap.size - 1); a barra tem que ficar do lado dele
        Vector2 topCenter = { basePos.x, basePos.y - (heap.size - 1) * offset };
        drawHeapRotBar(heap.data[0], topCenter, radius);
    }
}

void drawStackButtons(const ButtonVec& screenButtons) {
    for (int i = 0; i < screenButtons.size; i++) {
        const Button &b = screenButtons.buttons[i];
        if (b.type != STACK) continue;

        Vector2 basePos = { b.shape.x + b.shape.width / 2, b.shape.y + b.shape.height / 2 };
        drawStack(b.target, basePos);
    }
}

// Aspecto fixo da celula do atlas do player (24x54), nao do texture.width/height inteiro
// (que agora e 4 frames lado a lado).
Vector2 getSpritePos(Object& object) {
    float drawnWidth = PLAYER_HEIGHT * ((float)PLAYER_ATLAS_CELL_W / PLAYER_ATLAS_CELL_H);
    return (Vector2){object.pos.x - drawnWidth / 2, object.pos.y - PLAYER_HEIGHT / 2};
}

void hitboxDraw(const Object& object) {
    DrawCircleV(object.pos, object.radius, RED);
}

// Recorta o frame da animacao de andar (player.png, atlas 4 frames de 24x54 lado a lado).
// DIR_LEFT espelha o frame usando largura negativa na src (mesmo truque de warDetirps).
static void drawPlayerFrame(Sprite& sprite, Vector2 pos, float targetHeight, int frame, Direction dir) {
    float drawnWidth = targetHeight * ((float)PLAYER_ATLAS_CELL_W / PLAYER_ATLAS_CELL_H);

    float srcX = (float)(frame * PLAYER_ATLAS_CELL_W);
    float srcW = (float)PLAYER_ATLAS_CELL_W;
    if (dir == DIR_LEFT) {
        srcX += PLAYER_ATLAS_CELL_W; // espelha: comeca na borda direita da celula
        srcW = -srcW;
    }

    DrawTexturePro(
        sprite.texture,
        (Rectangle){srcX, 0, srcW, (float)PLAYER_ATLAS_CELL_H},
        (Rectangle){pos.x, pos.y, drawnWidth, targetHeight},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );
}

//COLOCAR CONST DEPOIS
void playerDraw(Player& player) {
    Vector2 spritePos = getSpritePos(player.object);
    drawPlayerFrame(player.object.sprite, spritePos, PLAYER_HEIGHT, player.animFrame, player.direction);
}

int drawNearestBut(const Player& player, const ButtonVec& screenButtons) {

    int index = nearestButtonIndex(player.object.pos.x, screenButtons);

    if(index != -1){
        const Button &b = screenButtons.buttons[index];
        DrawRectangle((int)b.shape.x, (int)b.shape.y, (int)b.shape.width, (int)b.shape.height, Fade(GREEN, BUTTON_OPACITY));
        // drawButGlow(b.shape, WHITE, CAMADAS_DE_BRILHO, BRILHO);
    }

    return index;
}


static bool isCookable(CookPoint p) {
    return p != NEEDS_TO_CUT;
}


static float cookFraction(CookPoint p) {
    if (p <= RAW) return 0.0f;
    return (float)p / (float)OVER_COOKED;
}

static const char* cookPointName(CookPoint p) {
    switch (p) {
        case NEEDS_TO_CUT: return "NEEDS TO BE CUT";
        case READY:        return "READY";
        case RAW:          return "RAW";
        case RARE:         return "RARE";
        case MEDIUM_RARE:  return "MEDIUM RARE";
        case WELL_DONE:    return "WELL DONE";
        case OVER_COOKED:  return "OVERCOOKED";
    }
    return "?";
}

static void drawCookBar(float rightEdge, float y, float barW, float barH, float frac) {
    Rectangle bg   = { rightEdge - barW, y, barW, barH };
    Rectangle fill = { bg.x, bg.y, bg.width * frac, bg.height };

    DrawRectangleRec(bg, DARKGRAY);
    DrawRectangleRec(fill, RED);
    DrawRectangleLinesEx(bg, 1.0f, BLACK);
}

// progresso dentro do estágio atual: 0 logo após mudar de estágio, 1 quando vai mudar
static float stageProgressOf(const CookInfo& ci, float stageTime) {
    if (ci.cookPoint >= OVER_COOKED) return 1.0f;  // queimado: barra cheia
    if (stageTime <= 0.0f) return 0.0f;

    float p = 1.0f - (ci.cook_time / stageTime);
    if (p < 0.0f) p = 0.0f;
    if (p > 1.0f) p = 1.0f;
    return p;
}

void drawCookInfo(Rectangle button, const CookState& cs, IngredientType type, MatchScreen screenId) {
    const int   fs     = 18;
    const float barH   = 6.0f;
    const float barW   = 130.0f;
    const float gap    = 4.0f;    // espaço entre texto e barra
    const float margin = 8.0f;    // espaço entre o bloco e o botão
    const int   lineH  = fs + (int)barH + 2 * (int)gap;

    const float stageTime = cookTimeOf(type);

    float rightEdge = button.x - margin;
    float y = button.y;

    const bool twoSided = (type == MEAT);

    if (twoSided) {
        // índice 0 = Baixo, índice 1 = Cima
        const char* labels[2] = { "Baixo", "Cima" };

        for (int side = 0; side < 2; side++) {
            const CookInfo& ci = cs.cookInfo[side];

            const char* txt = TextFormat("%s: %s", labels[side], cookPointName(ci.cookPoint));
            DrawText(txt, (int)(rightEdge - MeasureText(txt, fs)), (int)y, fs, GREEN);

            // só o lado de baixo avança; o de cima fica com a barra vazia
            float frac = 0.0f;
            if (isCookable(ci.cookPoint))
                frac = stageProgressOf(ci, stageTime);

            drawCookBar(rightEdge, y + fs + gap, barW, barH, frac);

            y += lineH;
        }
    } else {
        const CookInfo& ci = cs.cookInfo[0];

        // nome do estágio de cozimento (ex.: "Cru", "Pronto", ...)
        const char* txt = cookPointName(ci.cookPoint);
        DrawText(txt, (int)(rightEdge - MeasureText(txt, fs)), (int)y, fs, GREEN);

        // barra logo abaixo do texto
        float frac = isCookable(ci.cookPoint) ? stageProgressOf(ci, stageTime) : 0.0f;
        drawCookBar(rightEdge, y + fs + gap, barW, barH, frac);

        y += lineH;
    }

    if (cs.cooking) {
        const char* c = (screenId == BOARD) ? "Cutting" : "Cooking";
        DrawText(c, (int)(rightEdge - MeasureText(c, fs)), (int)y, fs, RED);
    }
}



void drawStackDetails(Button b){
    Color color;
    if (b.target.size <= (int)(b.target.capacity/4)) color = GREEN;
    else if (b.target.size <= (3*b.target.capacity/4)) color = YELLOW;
    else color = RED;
    DrawText(TextFormat("%d", b.target.size), (int)b.shape.x + 45, (int)b.shape.y - 30, 30, color);
}


// Desenha um hint de 2 linhas à direita do botão
static void drawCtrlHint(Rectangle button, const char* line2) {
    const int   fs     = 18;
    const float margin = 8.0f;

    float x = button.x + button.width + margin;
    float y = button.y;

    DrawText("CLICK", (int)x, (int)y,        fs, YELLOW);
    DrawText(line2,   (int)x, (int)y + fs + 2, fs, YELLOW);
}

void drawCtrlHintFor(Rectangle button, int screen) {
    if (!IsKeyDown(KEY_LEFT_CONTROL)) return;
    if (!CheckCollisionPointRec(GetMousePosition(), button)) return;

    if (screen == OVEN)       drawCtrlHint(button, "TO FLIP");
    else if (screen == BOARD) drawCtrlHint(button, "TO CUT");
}



void drawButtons(const ButtonVec& screenButtons, int butUnderMouseInd, MatchScreen screenId){

    for (int i = 0; i < screenButtons.size; i++) {

        if (screenId == FRIDGE && i != butUnderMouseInd) continue; // so desenha na geladeira se estiver abaixo do mouse

        const Button &b = screenButtons.buttons[i];

        // A tabua de corte (BOARD) ja tiene decoracao propria desenhada antes (drawBoard);
        // o retangulo verde generico so poluiria por cima dela.
        if (strcmp(b.text, "CUTTING BOARD") != 0) {
            DrawRectangle((int)b.shape.x, (int)b.shape.y, (int)b.shape.width, (int)b.shape.height, Fade(GREEN, BUTTON_OPACITY));
        }

        // Parte comum: círculo do ingrediente
        if (b.type == STACK || b.type == READIES_STACK) {
            Vector2 basePos = { b.shape.x + b.shape.width / 2, b.shape.y + b.shape.height / 2 };
            drawStack(b.target, basePos, INGREDIENT_RADIUS);
        }
        if ((b.type == INSERT || b.type == PICK) && b.target.size > 0) {
            Vector2 center = {b.shape.x + (b.shape.width/2), b.shape.y + (b.shape.height/2)};
            drawIngredient(center, INGREDIENT_RADIUS, b.target.top->data);
        }
        if (b.type == HEAP || b.type == READIES_HEAP) {
            Vector2 basePos = { b.shape.x + b.shape.width / 2, b.shape.y + b.shape.height / 2 };
            drawHeap(b.heap, basePos, INGREDIENT_RADIUS, 6.0f, i == butUnderMouseInd);
        }

        // Parte exclusiva de cada tipo
        switch (b.type) {
            case STACK: {
                drawStackDetails(b);

                // Converte b.target.type para texto legível utilizando o nome do ingrediente
                const char* stackLabel = (b.target.type == BURGER) ? "Burger" : 
                                         ((b.target.type == NONE) ? b.text : ingredientName((IngredientType)b.target.type));

                int fs = 18;
                int textWidth = MeasureText(stackLabel, fs);
                float textX = b.shape.x + (b.shape.width / 2.0f) - (textWidth / 2.0f);
                float textY = b.shape.y + b.shape.height + 6.0f; // 6 pixels ABAIXO do botão
                DrawText(stackLabel, (int)textX, (int)textY, fs, WHITE);
            } break;

            case INSERT: {
                if (b.target.size > 0) {
                    const Ingredient& ing = b.target.top->data;
                    drawCookInfo(b.shape, ing.cook_state, ing.type, screenId);

                if (i == butUnderMouseInd && (canFlip(ing.type) || isCuttable(ing.type)))
                    drawCtrlHintFor(b.shape, screenId);
                }
            } break;

            case PICK: {
                int fs = 20;
                int textWidth = MeasureText(b.text, fs);
                float textX = b.shape.x + (b.shape.width / 2.0f) - (textWidth / 2.0f);
                float textY = b.shape.y - fs - 6.0f; 
                DrawText(b.text, (int)textX, (int)textY, fs, WHITE);
            } break;

            case READIES_STACK:
            case HEAP:
            default: break;
        }
    }
    if(butUnderMouseInd != -1)
        drawButGlow(screenButtons.buttons[butUnderMouseInd].shape, WHITE, BRIGHTNESS_LAYERS, BRIGHTNESS);
}


//Camadas: Grossura do brilho. Alpha: O quanto brilha. Ambas são constantes em button_constants.hpp
//Essa função faz os botões brilharem
void drawButGlow(Rectangle r, Color cor, int camadas, float alpha){
    for (int i = 1; i <= camadas; i++)
    {
        Rectangle g = { r.x - i, r.y - i, r.width + i * 2, r.height + i * 2 };
        float a = alpha * (1.0f - (float)i / (camadas + 1));   // some com a distância
        DrawRectangleLinesEx(g, 1, Fade(cor, a));
    }
}

#define PATIENCE_BAR_W 60
#define PATIENCE_BAR_H 8
#define PATIENCE_BAR_GAP 6

// Barra de paciencia acima do costumer: verde (100-50%), amarelo (49-20%), vermelho (<20%)
static void drawPatienceBar(const Object& obj, float patience_time) {
    float pct = (patience_time / AVERAGE_COSTUMER_PATIENCE) * 100.0f;
    if (pct < 0)   pct = 0;
    if (pct > 100) pct = 100;

    Color color = (pct >= 50.0f) ? GREEN : (pct >= 20.0f) ? YELLOW : RED;

    Rectangle bg   = { obj.pos.x - PATIENCE_BAR_W / 2.0f, obj.pos.y - obj.radius - PATIENCE_BAR_H - PATIENCE_BAR_GAP, PATIENCE_BAR_W, PATIENCE_BAR_H };
    Rectangle fill = { bg.x, bg.y, bg.width * (pct / 100.0f), bg.height };

    DrawRectangleRec(bg, Fade(BLACK, 0.4f));
    DrawRectangleRec(fill, color);
    DrawRectangleLinesEx(bg, 1, BLACK);
}

#define ORDER_RECT_W 40
#define ORDER_RECT_H 16
#define ORDER_RECT_GAP 2

static void drawOrderBurger(const Costumer& cost) {
    float x = cost.obj.pos.x - ORDER_RECT_W / 2.0f;
    // deixa espaco acima da cabeca pra barra de paciencia nao sobrepor a lista do pedido
    float yBase = cost.obj.pos.y - cost.obj.radius - PATIENCE_BAR_H - PATIENCE_BAR_GAP - ORDER_RECT_H - ORDER_RECT_GAP;
    float step = ORDER_RECT_H + ORDER_RECT_GAP;

    // getCostumerOrder usa push_front, entao a lista fica na ordem inversa da string
    // (cost.order.start = ultimo ingrediente lido). Contamos antes pra desenhar o
    // primeiro no percorrido no topo (mais longe) em vez da base, restaurando a
    // ordem original: primeiro char da string na base, ultimo no topo.
    int count = 0;
    for (LinkedList_node<Ingredient>* p = cost.order.start; p != nullptr; p = p->prox) count++;

    if (count > 0) {
        Rectangle box = { x - ORDER_RECT_GAP, yBase - (count - 1) * step - ORDER_RECT_GAP,
                           ORDER_RECT_W + ORDER_RECT_GAP * 2 + ORDER_BOX_EXTRA_W, count * step + ORDER_RECT_GAP };
        DrawRectangleRec(box, Fade(BLACK, ORDER_BOX_OPACITY));
    }

    int index = count - 1;
    for (LinkedList_node<Ingredient>* p = cost.order.start; p != nullptr; p = p->prox) {
        Vector2 center = { x + ORDER_RECT_H / 2.0f, yBase - index * step + ORDER_RECT_H / 2.0f };
        drawIngredient(center, ORDER_RECT_H / 2.0f, p->data);

        const char* name = ingredientName(p->data.type);
        const char* cookLabel = nullptr;
        if (p->data.type == MEAT) {
            switch (practicalCookingStateOf(p->data)) {
                case RARE:        cookLabel = "Rare";       break;
                case MEDIUM_RARE: cookLabel = "Medium";     break;
                case WELL_DONE:   cookLabel = "Well Done";  break;
                case OVER_COOKED: cookLabel = "Overcooked"; break;
                default: break;
            }
        }

        const char* text = cookLabel ? TextFormat("%s (%s)", name, cookLabel) : name;
        const int fs = 12;
        DrawText(text, (int)(x + ORDER_RECT_H + 6), (int)(center.y - fs / 2), fs, WHITE);

        index--;
    }
}

static Color costumerColor(CostumerType type) {
    switch (type) {
        case CHILL_GUY: return BLUE;
        case MOA:       return LIGHTGRAY;
        case ALYSA:     return DARKGREEN;
        case TONY:      return MAROON;
        case SPEED:     return RED;
        default:        return PURPLE;
    }
}

// Setado uma vez em loadSpritesheet (match.spriteMatch[SPR_COSTUMERS]). drawCostumerBody
// usa o atlas se disponivel; sem ele (chamada antes do load) cai no circulo.
static Sprite* g_costumerAtlas = nullptr;

void setCostumerAtlas(Sprite& atlas) {
    g_costumerAtlas = &atlas;
}

// Desenha a celula do atlas correspondente ao tipo do cliente, centrada em `center`.
// Cada CostumerType valido (CHILL_GUY..VEGAN) e uma coluna, na ordem do enum.
static void drawCostumerSprite(Sprite& atlas, Vector2 center, CostumerType type) {
    Rectangle src = {
        (float)(type * COSTUMER_ATLAS_CELL_W),
        0,
        (float)COSTUMER_ATLAS_CELL_W,
        (float)COSTUMER_ATLAS_CELL_H
    };
    Rectangle dest = {
        center.x - COSTUMER_DRAW_W / 2.0f,
        center.y - COSTUMER_DRAW_H / 2.0f,
        COSTUMER_DRAW_W,
        COSTUMER_DRAW_H
    };

    DrawTexturePro(atlas.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
}

static void drawCostumerBody(const Costumer& cost) {
    if (g_costumerAtlas != nullptr) {
        drawCostumerSprite(*g_costumerAtlas, cost.obj.pos, cost.type);
    } else {
        DrawCircleV(cost.obj.pos, cost.obj.radius, costumerColor(cost.type));
    }
    drawPatienceBar(cost.obj, cost.patience_time);
}

// So os corpos (circulo/sprite + barra de paciencia). Chamar ANTES do background, pra ficar atras.
void drawCostumers(Queue<Costumer>& queue, Costumer counter[]) {
    for (Queue_node<Costumer>* aux = queue.first; aux != nullptr; aux = aux->prox) {
        Costumer& cost = aux->data;

        std::cout << cost.type << " drawn at: " << cost.obj.pos.x << " | ideal pos: " << cost.ideal_pos_x << "\n";
        drawCostumerBody(cost);
    }

    for (int i=0; i<COUNTER_SIZE; i++) {
        Costumer& cost = counter[i];
        if (cost.type == EMPTY) continue;

        std::cout << cost.type << " drawn at: " << cost.obj.pos.x << "\n";
        drawCostumerBody(cost);
    }
}

// So o balao do pedido do cliente sob o mouse. Chamar DEPOIS do background (e do player),
// pra ficar na frente de tudo.
void drawCostumerOrders(Costumer counter[], Vector2 mouseWorld) {
    for (int i=0; i<COUNTER_SIZE; i++) {
        Costumer& cost = counter[i];
        if (cost.type == EMPTY) continue;

        if (CheckCollisionPointCircle(mouseWorld, cost.obj.pos, cost.obj.radius)) {
            drawOrderBurger(cost);
        }
    }
}
