#include "../include/costumer.hpp"
#include "raylib.h"

void getCostumerOrder(LinkedList<Ingredient>& list, const int order_cod, const AVL& avl, const HashTable& ht) {
    //
    // DO THE HASHTABLE STUFF LATER
    //

    AVL_node* auxiliar_node = new AVL_node;
    auxiliar_node = searchAVL(avl.root, order_cod);

    std::string ingredient_string = auxiliar_node->data.ingredients;
    for (int i=0; i < ingredient_string.length(); i++) {
        Ingredient ing;
        initIngredient(ing, ingredient_string[i]);

        if (ing.type == MEAT || ing.type == VEGAN_PROTEIN) {
            CookPoint meat_point = (CookPoint) GetRandomValue(RARE, WELL_DONE);
            ing.cook_state.cookInfo[0].cookPoint = meat_point;
            ing.cook_state.cookInfo[1].cookPoint = meat_point;
        }

        push_front(list, ing);
    }
}

void initializeCostumer(Costumer& cost, const AVL& avl, const HashTable& ht) {
    cost.patience_time = AVERAGE_COSTUMER_PATIENCE;

    CostumerType type = (CostumerType) (GetRandomValue(CHILL_GUY, COSTUMER_TYPES_QUANTITY - 1));
    cost.type = type;

    initializeLinkedList(cost.order);
    int order_cod = GetRandomValue(1, avl.last_cod);
    getCostumerOrder(cost.order, order_cod, avl, ht);

    cost.obj.pos.y = COSTUMER_POS_Y;
    cost.obj.pos.x = -100; // Starts off the screen
    cost.obj.radius = 67;
}

void processCostumers(Queue<Costumer>& queue, Costumer counter[], const AVL& avl, const HashTable& ht) {
    // 1. Update queue
    if (queue.size < MAX_COSTUMER_QUEUE_SIZE) {
        std::cout << "Costumer timer: " << queue.costumer_timer << "\n";
        if (queue.costumer_timer < 0) {
            Costumer newCostumer;
            initializeCostumer(newCostumer, avl, ht);

            enqueue(queue, newCostumer);

            queue.costumer_timer = COSTUMER_TIMER_MAX;
        }
        queue.costumer_timer -= COSTUMER_TIMER_SPEED;
    }
    std::cout << "QUANTITY OF COSTUMERS: " << queue.size << std::endl;

    // 2. Process positions
    int i = 0;
    for (Queue_node<Costumer>* aux = queue.first; aux != nullptr; aux = aux->prox) {
        aux->data.ideal_pos_x = FIRST_COSTUMER_IN_QUEUE_POS_X - (i * COSTUMER_DELTA);

        if (aux->data.obj.pos.x < aux->data.ideal_pos_x) {
            aux->data.obj.pos.x += COSTUMER_SPEED;
        }

        i++;
    }

    // 3. Process counter positions
    for (int i = 0; i < COUNTER_SIZE; i++) {
        if (counter[i].type == EMPTY) continue;
        if (counter[i].obj.pos.x < counter[i].ideal_pos_x) {
            counter[i].obj.pos.x += COSTUMER_SPEED;
        }
    }
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
