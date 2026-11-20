#include <cstdio>
#include <cstring>

#include "../include/graphics.hpp"
#include "../include/camera.hpp"
#include "../include/button_constants.hpp"
#include "../include/inputs.hpp"
#include "raylib.h"


void drawMenu(const ButtonVec& menuButtons, int butUnderMouseInd){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "DADO BURGER";
        int titleFs = 60;
        DrawText(title, WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, 150, titleFs, DARKBROWN);

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

void drawHistory(const ContiguousList<PlayerInfo>& historico, int page, const ButtonVec& historyButtons, int butUnderMouseInd){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const char* title = "HISTORY";
        int titleFs = 50;
        DrawText(title, WINDOW_WIDTH / 2 - MeasureText(title, titleFs) / 2, 60, titleFs, DARKBROWN);

        int totalPages = (historico.size + HISTORY_ENTRIES_PER_PAGE - 1) / HISTORY_ENTRIES_PER_PAGE;
        if (totalPages < 1) totalPages = 1;

        int start = page * HISTORY_ENTRIES_PER_PAGE;
        int end   = start + HISTORY_ENTRIES_PER_PAGE;
        if (end > historico.size) end = historico.size;

        int y = HISTORY_LIST_TOP_Y;
        for (int i = start; i < end; i++) {
            const PlayerInfo &info = historico.data[i];
            DrawText(info.nome.c_str(), HISTORY_LIST_LEFT_X, y, 24, BLACK);
            DrawText(TextFormat("%d", info.score), HISTORY_LIST_LEFT_X + HISTORY_LIST_NAME_W, y, 24, BLACK);
            y += HISTORY_LIST_ROW_H;
        }

        const char* pageTxt = TextFormat("Page %d / %d", page + 1, totalPages);
        DrawText(pageTxt, WINDOW_WIDTH / 2 - MeasureText(pageTxt, 24) / 2, HISTORY_NAV_BUTTON_Y - 40, 24, DARKGRAY);

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

void drawKitchen(Match& match, int butUnderMouseInd){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const ButtonVec &buttonsVec = match.buttonsVec[match.screen];

        BeginMode2D(match.camera);
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), match.camera);
            drawCostumers(match.costumer_line, match.costumer_counter, mouseWorld);

            spriteDraw(match.spriteMatch[SPR_BACKGROUND], (Vector2){0, 0}, GAME_SCALE, WHITE);

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

        EndMode2D();

        drawInventory(match.player);

    EndDrawing();
}

void drawPrepare(Match &match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    const ButtonVec &buttonsVec = match.buttonsVec[match.screen];

    drawButtons(buttonsVec, butUnderMouseInd, match.screen);

    drawInventory(match.player);

    EndDrawing();
}


static void drawStackColumn(float x, int count) {
    float total  = count * STACK_H + (count - 1) * STACK_GAP;
    float startY = WINDOW_WIDTH / 2.0f - total / 2.0f;

    for (int i = 0; i < count; i++) {
        Rectangle r = { x, startY + i * (STACK_H + STACK_GAP), STACK_W, STACK_H };
        DrawRectangleRec(r, BLACK);
    }
}

void drawBoard(Match match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        // chão e paredes
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, LIGHTGRAY);
        DrawRectangleLinesEx((Rectangle){ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }, 12, DARKGRAY);

        // tábua
        Rectangle board = { BOARD_X, BOARD_Y, BOARD_W, BOARD_H };
        DrawRectangleRec(board, (Color){ 139, 90, 43, 255 });
        DrawRectangleLinesEx(board, 4, DARKBROWN);

        // 3 stacks à esquerda
        drawStackColumn(BOARD_X - STACK_MARGIN - STACK_W, STACKS_LEFT);

        // 2 stacks à direita
        drawStackColumn(BOARD_X + BOARD_W + STACK_MARGIN, STACKS_RIGHT);

        const ButtonVec &buttonsVec = match.buttonsVec[match.screen];
        drawButtons(buttonsVec, butUnderMouseInd, match.screen);

        drawInventory(match.player);

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

void drawStove(Match& match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        BeginMode2D(match.camera);

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

            const ButtonVec &buttonsVec = match.buttonsVec[match.screen];
            drawButtons(buttonsVec, butUnderMouseInd, match.screen);

        EndMode2D();

        drawInventory(match.player);

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
        case VEGAN_PROTEIN: return DARKGREEN;
        case EGG:           return RAYWHITE;
        case PICKLES:       return LIME;
        case CHEDDAR:       return ORANGE;
        case SWISS_CHEESE:  return GOLD;
        case UPPER_BREAD:   return BEIGE;
        default:            return BLANK;   // NONE ou ingrediente sem cor definida
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
            DrawCircleV(center, INV_SLOT_SIZE * 0.3f, ingredientColor(slot.type));

            // quantidade no canto inferior direito
            if (slot.size > 1)
                DrawText(TextFormat("%d", slot.size),
                         (int)(r.x + r.width - 22), (int)(r.y + r.height - 22), 20, WHITE);
        }
    }
}

Vector2 getSpritePos(Object& object) {
    return (Vector2){object.pos.x - (object.sprite.width * GAME_SCALE) / 2, object.pos.y - (object.sprite.height * GAME_SCALE) / 2};
}

void hitboxDraw(const Object& object) {
    DrawCircleV(object.pos, object.radius, RED);
}

//COLOCAR CONST DEPOIS
void playerDraw(Player& player) {
    Vector2 spritePos = getSpritePos(player.object);

    if (player.direction == DIR_RIGHT) {
        spriteDraw(player.object.sprite, spritePos, GAME_SCALE, WHITE);
    }
    if (player.direction == DIR_LEFT) {
        warDetirps(player.object.sprite, spritePos, GAME_SCALE, WHITE);
    }
}

int drawNearestBut(const Player& player, const ButtonVec& screenButtons) {

    int index = nearestButtonIndex(player.object.pos.x, screenButtons);

    if(index != -1){
        const Button &b = screenButtons.buttons[index];
        DrawRectangle((int)b.shape.x, (int)b.shape.y, (int)b.shape.width, (int)b.shape.height, GRAY);
        // drawButGlow(b.shape, WHITE, CAMADAS_DE_BRILHO, BRILHO);
        DrawText(b.text, (int)b.shape.x + 10, (int)b.shape.y + 10, 30, BLACK);
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

void drawCookInfo(Rectangle button, const CookState& cs, IngredientType type) {
    const int   fs     = 18;
    const float barH   = 6.0f;
    const float barW   = 130.0f;
    const float gap    = 4.0f;    // espaço entre texto e barra
    const float margin = 8.0f;    // espaço entre o bloco e o botão
    const int   lineH  = fs + (int)barH + 2 * (int)gap;

    const float stageTime = cookTimeOf(type);

    float rightEdge = button.x - margin;
    float y = button.y;

    const bool twoSided = (type == MEAT || type == VEGAN_PROTEIN);

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
        const char* c = "Cooking";
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

        const Button &b = screenButtons.buttons[i];

        DrawRectangle((int)b.shape.x, (int)b.shape.y, (int)b.shape.width, (int)b.shape.height, GRAY);
        DrawText(b.text, (int)b.shape.x + 10, (int)b.shape.y + 10, 30, BLACK);

        // Parte comum: círculo do ingrediente
        if (b.type == STACK || b.type == INSERT || b.type == PICK) {
            Vector2 center = {b.shape.x + (b.shape.width/2), b.shape.y + (b.shape.height/2)};
            DrawCircleV(center, b.shape.width/2, ingredientColor(b.target.type));
        }

        // Parte exclusiva de cada tipo
        switch (b.type) {
            case STACK: {
                drawStackDetails(b);
            } break;

            case INSERT: {
                if (b.target.size > 0) {
                    const Ingredient& ing = b.target.top->data;
                    drawCookInfo(b.shape, ing.cook_state, ing.type);

                if (i == butUnderMouseInd && (canFlip(ing.type) || isCuttable(ing.type)))
                    drawCtrlHintFor(b.shape, screenId);
                }
            } break;

            case PICK:
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

#define ORDER_RECT_W 40
#define ORDER_RECT_H 16
#define ORDER_RECT_GAP 2

static void drawOrderBurger(const Costumer& cost) {
    float x = cost.obj.pos.x - ORDER_RECT_W / 2.0f;
    float y = cost.obj.pos.y - cost.obj.radius - ORDER_RECT_H - ORDER_RECT_GAP;

    for (LinkedList_node<Ingredient>* p = cost.order.start; p != nullptr; p = p->prox) {
        Rectangle r = { x, y, ORDER_RECT_W, ORDER_RECT_H };
        DrawRectangleRec(r, ingredientColor(p->data.type));
        DrawRectangleLinesEx(r, 1, BLACK);
        y -= ORDER_RECT_H + ORDER_RECT_GAP;
    }
}

void drawCostumers(Queue<Costumer>& queue, Costumer counter[], Vector2 mouseWorld) {
    for (Queue_node<Costumer>* aux = queue.first; aux != nullptr; aux = aux->prox) {
            Costumer cost = aux->data;

            Color color;
            switch (cost.type) {
                case CHILL_GUY:
                    color = BLUE;
                    break;
                case NORMAL:
                    color = LIGHTGRAY;
                    break;
                case VEGAN:
                    color = DARKGREEN;
                    break;
                case TONY:
                    color = MAROON;
                    break;
                default:
                    color = PURPLE;
                    break;
            }

            std::cout << cost.type << " drawn at: " << cost.obj.pos.x << " | ideal pos: " << cost.ideal_pos_x << "\n";
            DrawCircleV(cost.obj.pos, cost.obj.radius, color);
    }

    for (int i=0; i<COUNTER_SIZE; i++) {
            Costumer cost = counter[i];

            if (cost.type != EMPTY) {

                Color color;
                switch (cost.type) {
                    case CHILL_GUY:
                        color = BLUE;
                        break;
                    case NORMAL:
                        color = LIGHTGRAY;
                        break;
                    case VEGAN:
                        color = DARKGREEN;
                        break;
                    case TONY:
                        color = MAROON;
                        break;
                    default:
                        color = PURPLE;
                        break;
                }

                std::cout << cost.type << " drawn at: " << cost.obj.pos.x << "\n";
                DrawCircleV(cost.obj.pos, cost.obj.radius, color);

                if (CheckCollisionPointCircle(mouseWorld, cost.obj.pos, cost.obj.radius)) {
                    drawOrderBurger(cost);
                }
            }
    }
}
