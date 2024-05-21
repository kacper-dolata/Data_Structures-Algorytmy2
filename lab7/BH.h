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

			tab[j]->parent = nullptr;
			tab[j]->left = nullptr;
			tab[j]->right = nullptr;

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
	Binary_Heap() {
		size = 0;
		capacity = 1;
		tab = new Node<T>*[capacity];
		for (int i = 0; i < capacity; i++) tab[i] = nullptr;
		root = nullptr;
	}
	Binary_Heap(Node<T>** in_tab, int in_size) {
		tab = in_tab;
		size = in_size;
		capacity = in_size;
		for (int i = 0; i < size; i++) heap_max(i);
		fix_a();
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
		for (int i = 0; i < size; i++) heap_max(i);
		size++;
		fix_a();
	}
	void remove_max() {
		size--;
		T tmp = tab[size]->data;
		tab[size]->data = tab[0]->data;
		tab[0]->data = tmp;

		if (tab[size] == tab[size]->parent->left) {
			tab[size]->parent->left = nullptr;
		}
		else if (tab[size] == tab[size]->parent->right) {
			tab[size]->parent->right = nullptr;
		}

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

		for (int i = 0; i < size; i++) heap_min(i);
		for (int i = 0; i < size; i++) heap_max(i);

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
			cout << "\narray is empty" << endl;
			return;
		}
		cout << "\ntabela: " << endl;
		for (int i = 0; i < size; i++)cout << "id nr " << i << ": " << tab[i]->data << endl;
		cout << "\ncapacity: " << capacity << "\nsize: " << size << endl;
		cout << "drzewo: " << endl;
		in_order(root);
	}
	void in_order(Node<T>* node) {
		if (node == nullptr) return;
		in_order(node->left);

		cout << "\n" << node->data << endl;

		in_order(node->right);
	}
	void sort() {
		Node<T>** sort_tab = new Node<T>*[capacity];
		for (int i = 0; i < size; i++) sort_tab[i] = new Node<T>;
		for (int j = capacity - 1; j >= 0; j--) {
			size--;
			T tmp = tab[size]->data;
			tab[size]->data = tab[0]->data;
			tab[0]->data = tmp;
			sort_tab[j]->data = tab[size]->data;

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

			for (int i = 0; i < size; i++) heap_min(i);
			for (int i = 0; i < size; i++) heap_max(i);
		}

		tab = sort_tab;
		fix_a();
		size = capacity;
		for (int i = 0; i < size; i++)cout << "id nr " << i << ": " << tab[i]->data << endl;
	}

};