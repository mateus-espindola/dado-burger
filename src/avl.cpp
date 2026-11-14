#include "../include/avl.hpp"
#include <string>

// AUX FUNCTIONS
int getAVLNodeLevel(AVL_node* node) {
    if (node == nullptr) return 0;
    return node->level;
}

int getAVLNodeBalanceFactor(AVL_node* node) {
    if (node == nullptr) return 0;
    return getAVLNodeLevel(node->left) - getAVLNodeLevel(node->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVL_node* rotationLL(AVL_node* y) {
    AVL_node* x = y->left;
    AVL_node* b = x->right;

    x->right = y;
    y->left = b;

    y->level = max(getAVLNodeLevel(y->left), getAVLNodeLevel(y->right)) + 1;
    x->level = max(getAVLNodeLevel(x->left), getAVLNodeLevel(x->right)) + 1;

    return x;
}

AVL_node* rotationRR(AVL_node* x) {
    AVL_node* y = x->right;
    AVL_node* b = y->left;

    y->left = x;
    x->right = b;

    x->level = max(getAVLNodeLevel(x->left), getAVLNodeLevel(x->right)) + 1;
    y->level = max(getAVLNodeLevel(y->left), getAVLNodeLevel(y->right)) + 1;

    return y;
}

AVL_node* rotationLR(AVL_node* z) {
    z->left = rotationRR(z->left);
    return rotationLL(z);
}

AVL_node* rotationRL(AVL_node* z) {
    z->right = rotationLL(z->right);
    return rotationRR(z);
}

AVL_node* balanceAVL(AVL_node* node) {
    node->level = max(getAVLNodeLevel(node->left), getAVLNodeLevel(node->right)) + 1;

    if (getAVLNodeBalanceFactor(node) >= 2 && getAVLNodeBalanceFactor(node->left) >= 0) {
        return rotationLL(node);
    }
    if (getAVLNodeBalanceFactor(node) <= -2 && getAVLNodeBalanceFactor(node->right) <= 0) {
        return rotationRR(node);
    }
    if (getAVLNodeBalanceFactor(node) >= 2 && getAVLNodeBalanceFactor(node->left) < 0) {
        return rotationLR(node);
    }
    if (getAVLNodeBalanceFactor(node) <= -2 && getAVLNodeBalanceFactor(node->right) > 0) {
        return rotationRL(node);
    }

    return node;
}



// MAIN FUNCTIONS
void initializeAVL(AVL& avl) {
    avl.root = nullptr;
}

AVL_node* insertAVL(AVL_node* root, const Order& order) {
    if (root == nullptr) {
        AVL_node* newNode = new AVL_node;
        newNode->data = order;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->level = 1;
        return newNode;
    }

    if (order.cod < root->data.cod) {
        root->left = insertAVL(root->left, order);
    }
    else if (order.cod > root->data.cod) {
        root->right = insertAVL(root->right, order);
    }

    return balanceAVL(root);
}

void printInOrderAVL(const AVL_node* root) {
    if (root == nullptr) return;

    printInOrderAVL(root->left);
    std::cout << "[" << root->data.cod << "] ";
    printInOrderAVL(root->right);
}

void exterminateAVL(AVL_node* root) {
    if (root == nullptr) return;

    exterminateAVL(root->left);
    exterminateAVL(root->right);

    delete root;
}

AVL_node* searchAVL(AVL_node* root, int cod) {
    if (root == nullptr) {
        return nullptr;
    }

    if (root->data.cod == cod) {
        return root;
    }
    else if (root->data.cod > cod) {
        return searchAVL(root->left, cod);
    }
    else {
        return searchAVL(root->right, cod);
    }
}


// #define MAX_NODES 999
// int main() {
//     AVL avl;

//     initializeAVL(avl);

//     Order orders[MAX_NODES];
//     for (int i=1; i<MAX_NODES; i++) {
//         orders[i] = (Order) {i, std::to_string(i)};
//         avl.root = insertAVL(avl.root, orders[i]);
//     }

//     printInOrderAVL(avl.root);
//     std::cout << "\n";

//     for (int i=1; i<MAX_NODES; i++) {
//         std::cout << getAVLNodeBalanceFactor(searchAVL(avl.root, i)) << " - ";
//     }

//     exterminateAVL(avl.root);
//     avl.root = nullptr; // After extermiFUCKINGnating the AVL, you must nulify the root pointer. -Obi Wan Kenobi

//     printInOrderAVL(avl.root);
//     std::cout << "\n";

//     return 0;
// }
