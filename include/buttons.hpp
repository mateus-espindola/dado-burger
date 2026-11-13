#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include "raylib.h"
#include "match_enums.hpp"
#include "tads.hpp"
#include "food.hpp"


/* ============================ */
/*            BUTTON            */
/* ============================ */

//NOTA: Para tu saber qual item tu ta pegando e so tirar a primeira letra da string do texto do botao
//Botoes de clicar
    //Clica e eles te trocam de ambiente ou algo assim
//Botoes de pegar item:
    //Verificam se tu tem alguma coisa na mao, se nao, pode pegar e se sim pega o item
//Botoes de insert:
    //Se tu tem item na mao, tu coloca o item (e se acapacidade nao estiver cheia, e claro)
    //Se nao tiver item na mao, tu pega o item
//Botoes de stack
    //Verificam clicks compostos (podemos diferenciar por click esquerdo e direito do mouse)
        //Com shift e pra tirar o item
            //Se nao tiver item nao faz nada
        //Sem shift tira o item
            //Se o stack tiver sem item, nao faz nada
enum ButtonType {
    CLICK,  //Click and does an action
    PICK,   //Click to pick an item
    DROP,   //Click to drop an item
    INSERT, //Click to put or pick an item
    STACK   //Click to put or take an item (usa shift (ou outra tecla) para diferenciar o click de tirar e colocar)
};

struct Button {
    ButtonType type;
    Rectangle shape;
    char text[20];
    Stack<Ingredient> *target;
    int targetCapacity;
    int targetSize;
};

struct ButtonVec {
    Button *buttons;
    int size;
};

void declareButtons(ButtonVec *screenButtons);

int nearestButtonIndex(const float playerX, const ButtonVec screenButtons);

int findButtonUnderMouse(Vector2 mouse, const ButtonVec &screenButtons, Camera2D camera, MatchScreen curScreen);

int setSquareButtons(Button *buttons, int startInd, int quantity, int delta, Rectangle shape, const char *text, ButtonType type, bool vertical);

#endif
