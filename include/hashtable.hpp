#include <iostream>
#include <string>
#include <type_traits>
#include "avl.hpp"


constexpr int HASHTABLE_CAPACITY = 11;

struct Hash_node{
	int key;
	Order data;
	Hash_node *next;
};

struct HashTable{
	int capacity;
	int size;
	float load_factor;
	Hash_node* data[HASHTABLE_CAPACITY];

	// boring stuff:
	int collisions;
	int hits;
	int misses;
};


// AUX FUNCTIONS

int knuth_hash(const int& key, const int& capacity);
void TEST_knush_hash(void);
int generate_hash_key(const Order& obj);
void update_load_factor(HashTable& ht);

// MAIN FUNCTIONS

void initializeHashTable(HashTable& ht);
void insertHashTable(HashTable& ht, const Order& obj);
void exterminateHashTable(HashTable& ht);



// int main() {
// 	HashTable<Order> hash_test;

// 	initializeHashTable(hash_test);

// 	TEST_knush_hash();

// 	Order burger1;
// 	burger1.cod = 67;
// 	burger1.order = "penis";

// 	insertHashTable(hash_test, burger1);

// 	exterminateHashTable(hash_test);

// 	return 0;
// }
