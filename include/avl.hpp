#include <string>
#include <iostream>

struct Order {
    int cod;
    std::string ingredients;
};

struct AVL_node {
    Order data;
    AVL_node *right;
    AVL_node *left;
    int level;
};

struct AVL {
    AVL_node *root;
};

// AUX FUNCTIONS
int getAVLNodeLevel(AVL_node* node);
int getAVLNodeBalanceFactor(AVL_node* node);
int max(int a, int b);
AVL_node* rotationLL(AVL_node* y);
AVL_node* rotationRR(AVL_node* x);
AVL_node* rotationLR(AVL_node* x);
AVL_node* rotationRL(AVL_node* x);
AVL_node* balanceAVL(AVL_node* node);

// MAIN FUNCTIONS
void initializeAVL(AVL& avl);
AVL_node* insertAVL(AVL_node* root, const Order& order);
void printInOrderAVL(const AVL_node* avl);
void exterminateAVL(AVL_node* root);
AVL_node* searchAVL(AVL_node* root, int cod);
