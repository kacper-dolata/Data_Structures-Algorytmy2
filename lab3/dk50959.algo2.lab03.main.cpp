//ALGO2 IS1 212B LAB03
//Kacper Dolata
//dk50959@zut.edu.pl

#include <iostream>
using namespace std;

template<typename T>
class Node{
public:
	T data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	Node(){
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
};
template<typename T>
class Tree{
	size_t height;
	Node<T>* root;

public:
	Tree(){
		root = nullptr;
		height = 0;
	}
	Node<T>* get_root(){
		return root;
	}
	void add(T input) {
		Node<T>* node = new Node<T>();
		Node<T>* temp = root;
		node->data = input;
		
		if(root==nullptr) {
			root = node;

		}
		else {
			while (true)
			{
				if (temp->data > node->data && temp->left == nullptr) {
					node->parent = temp;
					temp->left = node;
					return;
				}
				else if (temp->data < node->data && temp->right == nullptr) {
					node->parent = temp;
					temp->right = node;
					return;
				}
				else if(temp->data==node->data){
					cout << "nie moze byc taka sama wartosc" << endl;
					return;
				}

				if (temp->data > node->data) temp = temp->left; 
				else if (temp->data < node->data) temp = temp->right; 
			}
		}
	}
	Node<T>* search(T key, Node<T>*node) {
		if (node == nullptr) { 
			cout << "nie znaleziono" << endl;
			return node;
		}
		else if(node->data == key){
			return node;
		}
		else if(key < node->data) {
			search(key,node->left);
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
	void in_order(Node<T>* node) {
		if (node == nullptr) return;
		in_order(node->left);
		if(node->parent!=nullptr && node->parent->data > node->data)
			cout << "\n/ " << node->data << "\n";
		else if (node->parent != nullptr && node->parent->data < node->data)
			cout << "\n\\ " << node->data << "\n";
		else cout << "\n" << node->data << "\n";
		in_order(node->right);
	}
	void delete_node(T key) {
		if (root == nullptr) return;
		Node<T>* tmp = search(key, root);
		if (tmp != nullptr){
			if (tmp == root) remove_all(root);
			else if (tmp->left == nullptr && tmp->right == nullptr) {
				if (tmp->parent->left == tmp) {
					tmp->parent->left = nullptr;
				}
				else if (tmp->parent->right == tmp) {
					tmp->parent->right = nullptr;
				}
				delete tmp;
				tmp = nullptr;
			}
			else {
				Node<T>* sub = nullptr;
				if (tmp->data > root->data) {
					sub = tmp->right;
					if (sub->left != nullptr) {
						while (true) {
							if (sub->left == nullptr) break;
							sub = sub->left;
						}
					}
					sub->parent->left = nullptr;
					tmp->parent->right = sub;
				}
				else if (tmp->data < root->data) {
					sub = tmp->left;
					if (sub->right != nullptr) {
						while (true) {
							if (sub->right == nullptr) break;
							sub = sub->right;
						}
					}
					sub->parent->right = nullptr;
					tmp->parent->left = sub;
				}

				sub->parent = tmp->parent;
				sub->left = tmp->left;
				sub->right = tmp->right;
				if (sub->right != nullptr) sub->right->parent = sub;
				if (sub->left != nullptr) sub->left->parent = sub;

				delete tmp;
				tmp = nullptr;
			}
		}
	}
	void remove_all(Node<T>* node) {
		if(node!=nullptr)
		{
			remove_all(node->left);	
			remove_all(node->right);
			delete node;
			node = nullptr;
			root = nullptr;
		}
	}
	int display_height(Node<T>* node) {
		if (node == nullptr) return 0;

		int left_depth = display_height(node->left);
		int right_depth = display_height(node->right);

		if(left_depth>right_depth)return left_depth + 1;
		else return right_depth + 1;
	}
	void display_tree() {
		if (root == nullptr) {
			cout << "Drzewo nie istnieje!!!" << endl;
			return;
		}
		in_order(root);
		cout << endl;
	}
};



int main(){

	Tree<int>* tree = new Tree<int>();

	tree->add(7);
	tree->add(5);
	tree->add(3);
	tree->add(9);
	tree->add(4);
	tree->add(6);
	tree->display_tree();
	if (tree->display_height(tree->get_root()) > 0)
		cout << "wysokosc: " << tree->display_height(tree->get_root()) - 1 << endl;
	else cout << "wysokosc: 0" << endl;
	cout << "\nPo usunieciu: " << endl;
	tree->delete_node(-1);
	tree->display_tree();

	if(tree->display_height(tree->get_root())>0)
		cout << "wysokosc: " << tree->display_height(tree->get_root())-1 << endl;
	else cout << "wysokosc: 0" << endl;
	return 0;
}