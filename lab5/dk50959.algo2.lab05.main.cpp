//ALGO2 IS1 212B LAB05
//Kacper Dolata
//dk50959@zut.edu.pl


#include <iostream>
#include <string>
#include "DL_list.h"

using namespace std;

template<typename T>
class Hash_table {
	
	Linked_list<T>** table;
	int size;
	int capacity;

public:
	Hash_table() {
		size = 0;
		capacity = 1;
		table = new Linked_list<T>*[capacity];
		for (int i = 0; i < capacity; i++) {
			table[i] = nullptr;
		}
	}
	int hash_f(string s, int N) {

		int sum = 0;

		for (int i = 0; i < s.length(); i++) {
			sum = sum + (int(s[i]) * 31 ^ (s.length() - (i + 1)));
		}
		return sum % N;
	}
	void add_node(T input, string key) {
		while (true) {
			if (capacity == size) capacity *= 2;

			Linked_list<T>** new_table = new Linked_list<T>*[capacity];
			for (int i = 0; i < capacity; i++) {
				new_table[i] = nullptr;
			}

			int old_hash;
			int new_hash;
			Node<T>* old_node;

			for (int i = 0; i < size; i++)
			{
				if (table[i] != nullptr) {
					old_node = table[i]->search_return();
					while (true) {
						if (old_node == nullptr) break;

						old_hash = hash_f(old_node->key, size);
						new_hash = hash_f(old_node->key, size + 1);

						if (new_table[new_hash] == nullptr)
							new_table[new_hash] = new Linked_list<T>;

						new_table[new_hash]->add_end(old_node->data, old_node->key);
						old_node = old_node->next;
					}
				}
			}

			delete[] table;
			table = new_table;

			size++;
			int hash_key = hash_f(key, size);
			if (hash_key >= 0 && hash_key < size) {
				if (table[hash_key] == nullptr)
					table[hash_key] = new Linked_list<T>;
				table[hash_key]->add_end(input, key);
				return;
			}
		}
	}
	void search_node(string key) {
		int hash_key = hash_f(key, size);
		if (hash_key >= 0 || hash_key < size) {
			cout <<"Podany klucz: "<< key << " odpowiada indexowi nr. " << hash_key << ", ktory zawiera: ";
			table[hash_key]->display_all();
			cout << endl;
		}
		else cout << "nie ma takiego elementu" << endl;
	}
	void remove_node(string key) {
		int hash_key = hash_f(key, size);
		if (hash_key >= 0 || hash_key < size) {
			for (int i = 0; i < table[hash_key]->size_list(); i++) {
				table[hash_key]->search_remove(key);
			}
				
			if (table[hash_key]->size_list()==0) {
				size--;
				Linked_list<T>** new_table = new Linked_list<T>*[capacity];
				for (int i = 0; i < capacity; i++) {
					new_table[i] = nullptr;
				}

				int old_hash;
				int new_hash;
				Node<T>* old_node;

				for (int i = 0; i < size; i++)
				{
					if (table[i] != nullptr) {
						old_node = table[i]->search_return();
						while (true) {
							if (old_node == nullptr) break;
							old_hash = hash_f(old_node->key, size + 1);
							new_hash = hash_f(old_node->key, size);
							if (new_table[new_hash] == nullptr)
								new_table[new_hash] = new Linked_list<T>;
							new_table[new_hash]->add_end(old_node->data, old_node->key);
							old_node = old_node->next;
						}
					}
				}

				delete[] table;
				table = new_table;
			}

			cout << "usunieto" << endl;

		}else cout << "nie ma takiego elementu" << endl;
	}
	void remove_all() {
		for (int i = 0; i < size;i++) {
			if (table[i] != nullptr)
			{
				table[i]->remove_all();
				table[i] = nullptr;
			}
		}

		delete[] table;
		table = nullptr;
		cout << "usunieto" << endl;
	}
	void display() {
		if (table == nullptr) { cout << "array is empty!!!" << endl; return; }

		cout << "capacity: " << capacity << endl;
		cout << "size: " << size << endl;
		int Nempty = 0;
		cout << "\ntable:\n ";
		for (int i = 0; i < size; i++) {
			if (table[i] != nullptr) {
				cout << "index nr. " << i << " include: ";
				table[i]->display_all();
				cout << endl;
				Nempty++;
			}
		}
		cout << "\nstats:\nnon-null lists: " << Nempty << endl;
		int max = 0;
		
		for (int i = 0; i < size; i++) {
			if (table[i] != nullptr) {
				if (max < table[i]->size_list()) max = table[i]->size_list();
			}
		}
		cout << "list max size: " << max << endl;
	}
};

int main() {

	Hash_table<int>* tab = new Hash_table<int>();
	tab->add_node(15, "cat");
	tab->add_node(16, "cat");
	tab->add_node(11, "k");
	tab->add_node(17, "xzcas");
	tab->remove_node("cat");
	tab->display();

	return 0;
}