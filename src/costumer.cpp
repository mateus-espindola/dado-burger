#include <cmath>

#include "../include/costumer.hpp"
#include "raylib.h"
#include "../include/logs.hpp"

void getCostumerOrder(LinkedList<Ingredient>& list, const int order_cod, const AVL& avl, HashTable& ht) {
    Order order;

    if (!searchHashTable(ht, order_cod, order)) {
        Timer searchTimer;
        timer_iniciar(&searchTimer);

        AVL_node* node = searchAVL(avl.root, order_cod);
        order = node->data;

        double searchDuration = timer_parar(&searchTimer);

        // Acumula as métricas de busca da partida (conforme item 5.1)
        g_metrics.searchCount++;
        g_metrics.searchTime += searchDuration;
        // Nota: g_metrics.searchComparisons já foi incrementado dentro de searchAVL!

        insertHashTable(ht, order);
    }

    Ingredient lowerBread;
    initIngredient(lowerBread, 'y');

    push_front(list, lowerBread);

    std::string ingredient_string = order.ingredients;
    for (int i=0; i < ingredient_string.length(); i++) {
        Ingredient ing;
        initIngredient(ing, ingredient_string[i]);

        if (ing.type == MEAT) {
            CookPoint meat_point = (CookPoint) GetRandomValue(RARE, WELL_DONE);
            ing.cook_state.cookInfo[0].cookPoint = meat_point;
            ing.cook_state.cookInfo[1].cookPoint = meat_point;
        }
        else {
            ing.cook_state.cookInfo[0].cookPoint = READY;
            ing.cook_state.cookInfo[1].cookPoint = READY;
        }

        push_front(list, ing);
    }
}

void spiceCostumer(Costumer& cost) {
    Ingredient auxIng;

    switch (cost.type) {
        case CHILL_GUY:
            cost.patience_time *= 1.5f; // chill guy tem mais paciencia
        break;

        case VEGAN: {
            int idx = 0;
            LinkedList_node<Ingredient>* aux = cost.order.start;
            while (aux != nullptr) {
                LinkedList_node<Ingredient>* next = aux->prox;

                if (aux->data.type == MEAT) remove_at(cost.order, idx);
                else                        idx++;

                aux = next;
            }
        break;
        }

        case TONY: {
            cost.patience_time *= 0.67; // tony tem menos paciencia

            exterminateLinkedList(cost.order);

            initIngredient(auxIng, 'y');
            push_front(cost.order, auxIng);
            for (int i=0; i<GetRandomValue(TONYS_MIN_CHEESE, TONYS_MAX_CHEESE); i++) {
                char tonys_cheese_type;
                (GetRandomValue(0, 1) == 0) ? tonys_cheese_type = 'q' : tonys_cheese_type = 's';

                initIngredient(auxIng, tonys_cheese_type);
                CookPoint tonys_cheese_point = (CookPoint) GetRandomValue(NEEDS_TO_CUT, READY);
                auxIng.cook_state.cookInfo[0].cookPoint = tonys_cheese_point;
                auxIng.cook_state.cookInfo[1].cookPoint = tonys_cheese_point;

                push_front(cost.order, auxIng);
            }
            initIngredient(auxIng, 'z');
            push_front(cost.order, auxIng);

            break;
        }

        case SKELETON:
            initIngredient(auxIng, 'k');
            push_front(cost.order, auxIng); // ketchup em cima do hamburguer
        break;


        default: break;
    }
}

void initializeCostumer(Costumer& cost, const AVL& avl, HashTable& ht) {
    cost.patience_time = AVERAGE_COSTUMER_PATIENCE;

    CostumerType type = (CostumerType) (GetRandomValue(CHILL_GUY, COSTUMER_TYPES_QUANTITY - 1));
    cost.type = type;

    initializeLinkedList(cost.order);
    int order_cod = GetRandomValue(1, avl.last_cod);
    getCostumerOrder(cost.order, order_cod, avl, ht);
    spiceCostumer(cost);

    cost.obj.pos.y = COSTUMER_POS_Y;
    cost.obj.pos.x = -100; // Starts off the screen
    cost.obj.radius = 67;

    cost.leaving = false;
}

void processCostumers(Queue<Costumer>& queue, Costumer counter[], const AVL& avl, HashTable& ht) {
    // 1. Update queue
    if (queue.size < MAX_COSTUMER_QUEUE_SIZE && queue.costumers_generated < COSTUMERS_PER_MATCH) {
        std::cout << "Costumer timer: " << queue.costumer_timer << "\n";
        if (queue.costumer_timer < 0) {
            Costumer newCostumer;
            initializeCostumer(newCostumer, avl, ht);

            enqueue(queue, newCostumer);

            queue.costumers_generated++;
            queue.costumer_timer = COSTUMER_TIMER_MAX;
        }
        queue.costumer_timer -= COSTUMER_TIMER_SPEED;
    }
    std::cout << "QUANTITY OF COSTUMERS: " << queue.size << std::endl;

    // 2. Process positions
    int i = 0;
    Queue_node<Costumer>* prev = nullptr;
    Queue_node<Costumer>* aux = queue.first;
    while (aux != nullptr) {
        if (!aux->data.leaving) {
            aux->data.ideal_pos_x = FIRST_COSTUMER_IN_QUEUE_POS_X - (i * COSTUMER_DELTA);
        }

        float diff = aux->data.ideal_pos_x - aux->data.obj.pos.x;

        if (fabsf(diff) > COSTUMER_SPEED) {
            aux->data.obj.pos.x += (diff > 0 ? COSTUMER_SPEED : -COSTUMER_SPEED);
        } else {
            aux->data.obj.pos.x = aux->data.ideal_pos_x;
            if (aux->data.leaving) aux->data.type = EMPTY; // chegou fora da tela, libera o balcao
        }
        // na fila a paciencia cai na metade do ritmo normal
        // so decai enquanto nao esta saindo: senao fica eternamente <= 0 e o "if" abaixo
        // (sem esse guard) incrementaria costumers_that_left em todo frame da animacao de saida
        if (!aux->data.leaving) aux->data.patience_time -= COSTUMER_PATIENCE_DECAY / 2.0f;

        if (!aux->data.leaving && aux->data.patience_time <= 0.0f) {
            queue.costumers_that_left++;
            aux->data.leaving = true;
            aux->data.ideal_pos_x = -200.0f;
        }

        Queue_node<Costumer>* next = aux->prox;

        if (aux->data.type == EMPTY) {
            // saiu de tela: remove da fila de verdade. Sem isso o no fica fantasma pra
            // sempre e quem vem atras nunca reposiciona (ideal_pos_x usa o indice i).
            if (prev == nullptr) queue.first = next;
            else                 prev->prox = next;
            if (queue.last == aux) queue.last = prev;

            delete aux;
            queue.size--;
        } else {
            prev = aux;
            // quem ja esta saindo nao ocupa mais posicao na fila: isso faz os de tras
            // avancarem no mesmo frame em que o da frente desiste, nao so depois dele sair de tela
            if (!aux->data.leaving) i++;
        }

        aux = next;
    }

    // 3. Process counter positions
    for (int i = 0; i < COUNTER_SIZE; i++) {
        if (counter[i].type == EMPTY) continue;

        // Antes so movia pra direita (pos.x < ideal_pos_x). Pra sair pela esquerda
        // apos ser atendido precisa andar nos dois sentidos.
        float diff = counter[i].ideal_pos_x - counter[i].obj.pos.x;

        if (fabsf(diff) > COSTUMER_SPEED) {
            counter[i].obj.pos.x += (diff > 0 ? COSTUMER_SPEED : -COSTUMER_SPEED);
        } else {
            counter[i].obj.pos.x = counter[i].ideal_pos_x;
            if (counter[i].leaving) counter[i].type = EMPTY; // chegou fora da tela, libera o balcao
        }

        // no balcao a paciencia cai no ritmo normal, mas para de cair depois de atendido
        if (!counter[i].leaving) counter[i].patience_time -= COSTUMER_PATIENCE_DECAY;
        if (!counter[i].leaving && counter[i].patience_time <= 0.0f) {
            queue.costumers_that_left++;
            counter[i].leaving = true;
            counter[i].ideal_pos_x = -200.0f;
        }
    }
}

// Empilha o pedido na mesma ordem fisica que a montagem normal produziria: desce a lista
// recursivamente primeiro e so empilha ao desenrolar, entao order.start (topo do pedido)
// acaba virando o topo da pilha tambem - igual ao que compare_hamburger_with_order espera.
static void pushOrderOntoStack(Stack& burger, LinkedList_node<Ingredient>* node) {
    if (node == nullptr) return;
    pushOrderOntoStack(burger, node->prox);
    stack_push(burger, node->data);
}

// Cheat/debug: monta um hamburguer identico ao pedido do cliente embaixo do mouse e entrega
bool cheatGivePerfectBurger(Costumer counter[], Player& player, Vector2 mouseWorld) {
    for (int i = 0; i < COUNTER_SIZE; i++) {
        if (counter[i].type == EMPTY || counter[i].leaving) continue;
        if (!CheckCollisionPointCircle(mouseWorld, counter[i].obj.pos, counter[i].obj.radius)) continue;

        Stack& inventory = player.inventory[player.selectedSlot];
        stack_destroy(inventory); // limpa o que tiver na mao antes de montar o perfeito

        pushOrderOntoStack(inventory, counter[i].order.start);
        inventory.type = BURGER; // stack_push so marca isso sozinho se a pilha estava vazia
        inventory.capacity = lengthLinkedList(counter[i].order);

        return giveBurgerToCostumer(counter, player, mouseWorld);
    }

    return false;
}

bool giveBurgerToCostumer(Costumer counter[], Player& player, Vector2 mouseWorld) {
    Stack& inventory = player.inventory[player.selectedSlot];
    if (inventory.type != BURGER) return false;

    for (int i = 0; i < COUNTER_SIZE; i++) {
        if (counter[i].type == EMPTY || counter[i].leaving) continue;
        if (!CheckCollisionPointCircle(mouseWorld, counter[i].obj.pos, counter[i].obj.radius)) continue;

        float hambAccuracy = compare_hamburger_with_order(inventory, counter[i].order);

        player.money += (int) (hambAccuracy * MONEY_PER_PERFECT_BURGER);

        stack_destroy(inventory); // consome o hamburguer da mao (ja deixa type/size zerados)
        inventory.capacity = 1;  // devolve a capacidade padrao da mao (foi ampliada pra caber o hamburguer)

        counter[i].leaving = true;
        counter[i].ideal_pos_x = -200.0f; // sai pela esquerda da tela

        return true;
    }

    return false;
}

bool callCostumer(Queue<Costumer>& queue, Costumer counter[]) {
    if (isEmptyQueue(queue)) return false;

    for (int i=0; i<COUNTER_SIZE; i++) {
        // Aceita tambem slot com cliente ainda saindo (leaving): ja foi atendido,
        // nao precisa esperar a animacao de saida terminar pra chamar o proximo.
        if (counter[i].type == EMPTY || counter[i].leaving) {
            Costumer calledCost;
            dequeue(queue, &calledCost);

            calledCost.ideal_pos_x = COSTUMER_COUNTER_POS_X[i];

            counter[i] = calledCost;

            return true;
        }
    }

    return false;
}
