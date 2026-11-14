#include "../include/hashtable.hpp"

// AUX FUNCTIONS

int knuth_hash(const int& key, const int& capacity) {
	double KNUTH_CONSTANT = 0.6180339887;
	double frac = key * KNUTH_CONSTANT - (int)(key * KNUTH_CONSTANT);
	return (int) (capacity * frac);
}

void TEST_knush_hash(void) {
	for (int i=0; i<50; i++) {
		std::cout << i << ": " << knuth_hash(i, HASHTABLE_CAPACITY) << "\n";
	}
}

// fiz essa função de gerar a chave da tabela hash de acordo com o tipo, para se manter na proposta de fazer uma tabela hash genérica
// essa std::is_same_v bizarrinha serve para verificar se dois tipos são iguais
int generate_hash_key(const Order& obj) {
		return obj.cod;
}

void update_load_factor(HashTable& ht) {
	ht.load_factor = ht.size/ht.capacity;
}


// MAIN FUNCTIONS

void initializeHashTable(HashTable& ht) {
	ht.capacity = HASHTABLE_CAPACITY;
	ht.size = 0;
	ht.load_factor = 0.0f;

	for (int i=0; i<ht.capacity; i++) {
		ht.data[i] = nullptr;
	}

	ht.collisions = 0;
	ht.hits = 0;
	ht.misses = 0;
}

void insertHashTable(HashTable& ht, const Order& obj) {
	int new_key = generate_hash_key(obj);

	int i = knuth_hash(new_key, HASHTABLE_CAPACITY);

	if (ht.data[i] != nullptr) {
		ht.collisions++;
	}

	Hash_node *new_node = new Hash_node;

	new_node->key = new_key;
	new_node->data = obj;
	new_node->next = ht.data[i];

	ht.data[i] = new_node;
	ht.size++;
	update_load_factor(ht);
}

void exterminateHashTable(HashTable& ht) {
	for (int i=0; i < HASHTABLE_CAPACITY; i++) {
		Hash_node* current = ht.data[i];

		while (current != nullptr) {
			Hash_node* aux = current;
			current = current->next;
			delete aux;
		}

		ht.data[i] = nullptr;
	}

	ht.size = 0;
	ht.load_factor = 0.0f;
}
