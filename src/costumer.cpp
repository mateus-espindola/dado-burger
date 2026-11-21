#include <cmath>

#include "../include/costumer.hpp"
#include "raylib.h"

void getCostumerOrder(LinkedList<Ingredient>& list, const int order_cod, const AVL& avl, HashTable& ht) {
    Order order;

    if (!searchHashTable(ht, order_cod, order)) {
        AVL_node* node = searchAVL(avl.root, order_cod);
        order = node->data;
        insertHashTable(ht, order);
    }

    Ingredient lowerBread;
    initIngredient(lowerBread, 'y');

    push_front(list, lowerBread);

    std::string ingredient_string = order.ingredients;
    for (int i=0; i < ingredient_string.length(); i++) {
        Ingredient ing;
        initIngredient(ing, ingredient_string[i]);

        if (ing.type == MEAT || ing.type == VEGAN_PROTEIN) {
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

void initializeCostumer(Costumer& cost, const AVL& avl, HashTable& ht) {
    cost.patience_time = AVERAGE_COSTUMER_PATIENCE;

    CostumerType type = (CostumerType) (GetRandomValue(CHILL_GUY, COSTUMER_TYPES_QUANTITY - 1));
    cost.type = type;

    initializeLinkedList(cost.order);
    int order_cod = GetRandomValue(1, avl.last_cod);
    getCostumerOrder(cost.order, order_cod, avl, ht);

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
        aux->data.patience_time -= COSTUMER_PATIENCE_DECAY / 2.0f;
        if (aux->data.patience_time <= 0.0f) {
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
        if (counter[i].patience_time <= 0.0f ){
            counter[i].leaving = true;
            counter[i].ideal_pos_x = -200.0f;
        }
    }
}

bool giveBurgerToCostumer(Costumer counter[], Player& player, Vector2 mouseWorld) {
    Stack& inventory = player.inventory[player.selectedSlot];
    if (inventory.type != BURGER) return false;

    for (int i = 0; i < COUNTER_SIZE; i++) {
        if (counter[i].type == EMPTY || counter[i].leaving) continue;
        if (!CheckCollisionPointCircle(mouseWorld, counter[i].obj.pos, counter[i].obj.radius)) continue;

        float hambAccuracy = compare_hamburger_with_order(inventory, counter[i].order);

        player.money += (int) hambAccuracy * MONEY_PER_PERFECT_BURGER;

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
        if (counter[i].type == EMPTY) {
            Costumer calledCost;
            dequeue(queue, &calledCost);

            calledCost.ideal_pos_x = COSTUMER_COUNTER_POS_X[i];

            counter[i] = calledCost;

            return true;
        }
    }

    return false;
}
