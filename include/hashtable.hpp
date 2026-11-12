#include <iostream>
#include <string>
#include <type_traits>

constexpr int HASHTABLE_CAPACITY = 11;

struct Order {
	int cod;
	std::string order;
};	

template <typename T>
struct Hash_node{
	int key;
	T data;
	Hash_node *next;
};

template <typename T>
struct HashTable{
	int capacity;
	int size;
	float load_factor;
	Hash_node<T>* data[HASHTABLE_CAPACITY];

	// boring stuff:
	int collisions;
	int hits;
	int misses;
};



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
template <typename T>
int generate_hash_key(const T& obj) {
	if constexpr (std::is_same_v<T, Order>) {
		return obj.cod;
	}

	else return 0;
}

template <typename T>
void update_load_factor(HashTable<T>& ht) {
	ht.load_factor = ht.size/ht.capacity;
}


// MAIN FUNCTIONS

template <typename T>
void initializeHashTable(HashTable<T>& ht) {
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

template <typename T>
void insertHashTable(HashTable<T>& ht, const T& obj) {
	int new_key = generate_hash_key(obj);
	
	int i = knuth_hash(new_key, HASHTABLE_CAPACITY);

	if (ht.data[i] != nullptr) {
		ht.collisions++;
	}

	Hash_node<T> *new_node = new Hash_node<T>;

	new_node->key = new_key;
	new_node->data = obj;
	new_node->next = ht.data[i];
	
	ht.data[i] = new_node;
	ht.size++;
	update_load_factor(ht);
}

template <typename T>
void exterminateHashTable(HashTable<T>& ht) {
	for (int i=0; i < HASHTABLE_CAPACITY; i++) {
		Hash_node<T>* current = ht.data[i];

		while (current != nullptr) {
			Hash_node<T>* aux = current;
			current = current->next;
			delete aux;
		}

		ht.data[i] = nullptr;
	}

	ht.size = 0;
	ht.load_factor = 0.0f;
}



int main() {
	HashTable<Order> hash_test;

	initializeHashTable(hash_test);

	TEST_knush_hash();

	Order burger1;
	burger1.cod = 67;
	burger1.order = "penis";

	insertHashTable(hash_test, burger1);

	exterminateHashTable(hash_test);

	return 0;
}
