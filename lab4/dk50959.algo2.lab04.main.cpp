//ALGO2 IS1 212B LAB04
//Kacper Dolata
//dk50959@zut.edu.pl

#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

template<typename T>
class Node {
public:
	T data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	bool color; // 0-red, 1-black
	Node() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		color = 0;
	}
};

template<typename T>
class Tree {
	Node<T>* root;
	size_t size;
	void rotate_left(Node<T>* child, Node<T>* parent){
		child->parent = parent->parent;
		if(parent->parent != nullptr && parent==parent->parent->left)
			parent->parent->left=child;
		else if(parent->parent!=nullptr)
			parent->parent->right = child;

		parent->right = child->left;
		if(child->left!=nullptr)
			child->left->parent = parent;
		child->left = parent;
		parent->parent = child;

	}
	void rotate_right(Node<T>* child, Node<T>* parent) {
		child->parent = parent->parent;
		if (parent->parent != nullptr && parent == parent->parent->left)
			parent->parent->left = child;
		else if (parent->parent != nullptr)
			parent->parent->right = child;

		parent->left = child->right;
		if (child->right != nullptr)
			child->right->parent = parent;
		child->right = parent;
		parent->parent = child;
	}
	void fix_add(Node<T>* node) {

		while (true) {

			if (node->parent == nullptr || node->parent->color == 1) return;
			else if (node->parent->color == 0) {

				Node<T>* uncle = nullptr;
				Node<T>* parent = node->parent;
				Node<T>* grandparent = node->parent->parent;

				if (parent->data > grandparent->data) uncle = grandparent->left;
				else if (parent->data < grandparent->data) uncle = grandparent->right;

				if (uncle == nullptr || uncle->color == 1) {
					if (parent->data > grandparent->data && node->data > parent->data) {
						//line \ 
						rotate_left(parent, grandparent);
						parent->color = 1;
						grandparent->color = 0;

						if (grandparent == root) root = parent;
						//solution rotate left parent grandparent, recolor parent and grandparent
					}
					else if (parent->data < grandparent->data && node->data < parent->data) {
						//line /
						rotate_right(parent, grandparent);
						parent->color = 1;
						grandparent->color = 0;

						if (grandparent == root) root = parent;
						//solution rotate right parent grandparent, recolor parent and grandparent
					}
					else if (parent->data < grandparent->data && node->data > parent->data) {
						//triangle <
						rotate_left(node, parent);
						rotate_right(node, grandparent);
						node->color = 1;
						grandparent->color = 0;
						node = parent;
						if (grandparent == root) root = node;
						//solution rotate left node parent, recolor node and grandparent
					}
					else if (parent->data > grandparent->data && node->data < parent->data) {
						//triangle >
						rotate_right(node, parent);
						rotate_left(node, grandparent);
						node->color = 1;
						grandparent->color = 0;
						node = parent;
						if (grandparent == root) root = node;
						//solution rotate right node parent, recolor node and grandparent
					}
				}
				else if (uncle->color == 0) {
					uncle->color = 1;
					parent->color = 1;
					if (grandparent != root) {
						grandparent->color = 0;
						node = grandparent;
					}
				}
			}
		}
	}

public:
	Tree() {
		root = nullptr;
		size = 0;
	}
	Node<T>* search(T key, Node<T>* node) {
		if (node == nullptr) {
			cout << "nie znaleziono" << endl;
			return node;
		}
		else if (node->data == key) {
			return node;
		}
		else if (key < node->data) {
			search(key, node->left);
		}
		else if (key > node->data) {
			search(key, node->right);
		}
	}
	void pre_order(Node<T>* node) {
		if (node == nullptr) return;
		cout << " \n" << node->data << "\n ";
		pre_order(node->left);
		pre_order(node->right);
	}
	void in_order(Node<T>* node, HANDLE hConsole) {
		if (node == nullptr) return;

		in_order(node->left,hConsole);

		if (!node->color)SetConsoleTextAttribute(hConsole, 0x0C);
		else SetConsoleTextAttribute(hConsole, 0x70);
		if (node->parent != nullptr && node->parent->data > node->data)
			cout << "\n/ " << node->data << " kolor: " << node->color << "\n";
		else if (node->parent != nullptr && node->parent->data < node->data)
			cout << "\n\\ " << node->data << " kolor: " << node->color << "\n";
		else cout << "\n" << node->data << " kolor: " << node->color << "\n";

		in_order(node->right,hConsole);
	}
	void remove_all(Node<T>* node) {
		if (node != nullptr)
		{
			remove_all(node->left);
			remove_all(node->right);
			delete node;
			node = nullptr;
			root = nullptr;
		}
	}
	void display_tree() {
		if (root == nullptr) {
			cout << "Drzewo nie istnieje!!!" << endl;
			return;
		}

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		in_order(root,hConsole);
		SetConsoleTextAttribute(hConsole, 0x07);
		cout << endl;
	}
	void display_height() {
		cout << "\nWysokosc: " << round(2 * log((size + 1))) << endl;
	}
	void add_node(T input){
		
		Node<T>* node = new Node<T>;
		node->data = input;

		if (root==nullptr) {
			root = node;
			node->color = 1;
		}
		else {
			Node<T>* temp = root;

			while (true)
			{
				if (temp->data > node->data && temp->left == nullptr) {
					node->parent = temp;
					temp->left = node;
					break;
				}
				else if (temp->data < node->data && temp->right == nullptr) {
					node->parent = temp;
					temp->right = node;
					break;
				}
				else if (temp->data == node->data) {
				cout << "nie moze byc taka sama wartosc" << endl;
				return;
				}

				if (temp->data > node->data) temp = temp->left;
				else if (temp->data < node->data) temp = temp->right;
			}
		}
		size++;
		fix_add(node);
	}
};

int main(){
	Tree<int>* tree = new Tree<int>;

	tree->add_node(10);
	tree->add_node(18);
	tree->add_node(7);
	tree->add_node(15);
	tree->add_node(16);
	tree->add_node(30);
	tree->add_node(25);
	tree->add_node(40);
	tree->add_node(60);
	tree->add_node(2);
	tree->add_node(1);
	tree->add_node(70);

	tree->display_tree();
	tree->display_height();

	return 0;
}