#pragma once
#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Node
{
public:
	T data;
	string key;
	Node<T>* next;
	Node<T>* prev;
	Node()
	{
		key = "";
		next = nullptr;
		prev = nullptr;
	}
};

template<typename T>
class Linked_list
{
	Node<T>* head;
	Node<T>* tail;
	size_t size;

public:
	Linked_list()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	void add_end(T input, string key)
	{
		Node<T>* node = new Node<T>;
		node->data = input;
		node->key = key;

		if (tail == nullptr)
		{
			head = node;
			tail = node;
			size++;
		}
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
			size++;
		}
	}
	void add_front(T input, string key)
	{
		Node<T>* node = new Node<T>;
		node->data = input;
		node->key = key;

		if (head == nullptr)
		{
			head = node;
			tail = node;
			size++;
		}
		else
		{
			head->prev = node;
			node->next = head;
			head = node;
			size++;
		}
	}
	void add_on_index(T input, string key, int choice)
	{
		Node<T>* node = new Node<T>;
		Node<T>* temp = head;
		int choice, i = 0;

		node->data = input;
		node->key = key;

		if (head == nullptr)
		{
			head = node;
			tail = node;
			size++;
		}

		if (choice<0 || choice>size)
		{
			cout << "nieprawidlowy index!!!" << endl;
			return;
		}
		if (choice == 0)
		{
			head->prev = node;
			node->next = head;
			head = node;
			size++;
			cout << "dodano pomyslnie" << endl;
			return;
		}
		else if (choice == size)
		{

			tail->next = node;
			node->prev = tail;
			tail = node;
			size++;
			cout << "dodano pomyslnie" << endl;
			return;

		}
		while (choice - 1 != i)
		{
			temp = temp->next;
			i++;
		}

		node->next = temp->next;
		temp->next->prev = node;
		temp->next = node;
		node->prev = temp;
		size++;
		//cout << "dodano pomyslnie" << endl;
	}
	void change_on_index(T input, string key, int choice)
	{
		Node<T>* temp = head;
		int i = 0;

		if (choice<0 || choice>size - 1)
		{
			cout << "nieprawidlowy index!!!" << endl;
			return;
		}

		while (choice != i)
		{
			temp = temp->next;
			i++;
		}

		temp->data = input;
		temp->key = key;
	}
	void remove_front()
	{
		if (head == nullptr) { return; }
		
		if (head->next != nullptr) {
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		else {
			delete head; 
			head = nullptr;
		}
			
		size--;
		
	}
	void remove_end()
	{
		if (tail == nullptr) { return; }

		tail = tail->prev;
		tail->prev->next = tail;
		size--;

		delete tail->next;
		tail->next = nullptr;
	}
	void remove_all()
	{
		Node<T>* temp = head;
		if (size == 0) { cout << " lista jest pusta!!! " << endl; return; }

		while (size != 0)
		{
			if (temp->next == nullptr) { delete temp; return; }
			temp = temp->next;
			delete temp->prev;
			size--;
		}
	}
	void display_all()
	{
		Node<T>* temp = head;

		if (size == 0) { cout << " lista jest pusta!!! " << endl; return; }

		for (int i = 0; i < size; i++)
		{
			cout << temp->data << ", ";
			if (temp->next == nullptr) break;
			temp = temp->next;
		}
	}
	void display_index(int choice)
	{
		Node<T>* temp = head;
		int i = 0;

		if (size == 0) { cout << " lista jest pusta!!! " << endl; return; }

		if (choice<0 || choice>size - 1)
		{
			cout << "nieprawidlowy index!!!" << endl;
			return;
		}

		while (choice != i)
		{
			temp = temp->next;
			i++;
		}
		cout << temp->data << endl;
	}
	void search(T key)
	{
		Node<T>* temp = head;
		if (size == 0) { cout << " lista jest pusta!!! " << endl; return; }

		while (temp->data != key)
		{
			if (temp->next == nullptr)
			{
				cout << " nie znaleziono " << endl;
				return;
			}
			temp = temp->next;
		}
		cout << temp->data << endl;
	}
	void search_remove(string key)
	{
		Node<T>* temp = head;

		if (size == 0) { cout << " lista jest pusta!!! " << endl; return; }

		while (temp->key != key)
		{
			if (temp->next == nullptr)
			{
				return;
			}
			temp = temp->next;
		}

		if (temp == tail)
		{
			remove_end();
		}
		else if (temp == head)
		{
			remove_front();
		}
		else
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			size--;
			delete temp;
			temp = nullptr;
		}
	}
	Node<T>* search_return() {
		if (head == nullptr) return head; 
		return head;
	}
	int size_list()
	{
		return size;
	}
};