//ALGO2 IS1 212B LAB06
//Kacper Dolata
//dk50959@zut.edu.pl

#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
	T data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;

	Node() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
};

template<typename T>
class Binary_Heap {
	int size;
	int capacity;
	Node<T>** tab;
	Node<T>* root;

	void heap_max(int id) {
		if (id > 0) {
			int parent = id / 2;
			if (tab[parent]->data < tab[id]->data) {
				swap(tab[parent], tab[id]);
				heap_max(parent);
			}
			else return;
		}
	}
	void heap_min(int id) {
		if (id > 0) {
			int parent = id / 2;
			if (tab[parent]->data > tab[id]->data) {
				swap(tab[parent], tab[id]);
				heap_min(parent);
			}
			else return;
		}
	}
	void fix_a() {
		for (int j = 0; j < size; j++) {
			if (j > 0)
				tab[j]->parent = tab[(j - 1) / 2];
			if ((2 * j + 1) < size)
				tab[j]->left = tab[2 * j + 1];
			if ((2 * j + 2) < size)
				tab[j]->right = tab[2 * j + 2];
		}
		root = tab[0];
	}
public:
	Binary_Heap(){
		size = 0;
		capacity = 1;
		tab = new Node<T>*[capacity];
		for (int i = 0; i < capacity; i++) tab[i] = nullptr;
		root = nullptr;
	}
	void add(T input) {
		Node<T>* node = new Node<T>();
		node->data = input;
		if (capacity == size)
		{
			capacity *= 2;
			Node<T>** new_tab = new Node<T>*[capacity];
			for (int i = 0; i < capacity; i++) new_tab[i] = nullptr;

			for (int i = 0; i < size; i++)
			{
				new_tab[i] = tab[i];
			}
			delete[] tab;
			tab = new_tab;
		}
		
		tab[size] = node;
		heap_max(size);
		fix_a();
		size++;
	}
	void remove_max() {
		size--;
		swap(tab[size], tab[0]);
		delete tab[size];
		tab[size] = nullptr;

		Node<T>** new_tab = new Node<T>*[size];
		for (int i = 0; i < size; i++) new_tab[i] = nullptr;

		for (int i = 0; i < size; i++)
		{
			new_tab[i] = tab[i];
		}
		delete[] tab;
		tab = new_tab;

		heap_min(size - 1);
		heap_max(size - 1);
		fix_a();
	}
	void remove_all() {
		for (int i = 0; i < size; i++) {
			delete tab[i];
			tab[i] = nullptr;
		}
		delete[] tab;
		tab = nullptr;
		root = nullptr;
		size = 0;
		capacity = 1;
	}
	void display() {
		if (size == 0)
		{
			cout << "array is empty" << endl;
			return;
		}
		for (int i = 0; i < size; i++)cout << "id nr " << i << ": " << tab[i]->data << endl;
		cout << "\ncapacity: " << capacity << "\nsize: " << size << endl;
		in_order(root);
	}
	void in_order(Node<T>* node) {
		if (node == nullptr) return;
		in_order(node->left);
		
		cout << "\n" << node->data << endl;
		
		in_order(node->right);
	}
	
};

int main() {

	Binary_Heap<int>* heap = new Binary_Heap<int>();
	heap->add(5);
	heap->add(10);
	heap->add(15);
	heap->add(20);
	heap->display();
	heap->remove_max();
	heap->display();
	heap->remove_all();
	heap->display();

	return 0;
}