//ALGO2 IS1 212B LAB07
//Kacper Dolata
//dk50959@zut.edu.pl
#include <iostream>
#include "BH.h"

using namespace std;

void heap_sort() {
	Node<int>** tab = new Node<int>*[10];
	for (int i = 0; i < 10; i++) {
		tab[i] = new Node<int>();
		tab[i]->data = 10 - i;
	}
	Binary_Heap<int>* heap = new Binary_Heap<int>(tab, 10);
	heap->sort();
}
void count_sort(int* tab, int size, int m) {
	for (int i = 0; i < size; i++) {
		if (tab[i] < 0) {
			cout << "niezgodnosc z dziedzina,\n element w tablicy powinny byc wieksze lub rowne 0" << endl;
			return;
		}
	}
	m += 1;
	int* counter = new int[m];
	int* new_tab = new int[size];
	for (int i = 0; i < m; i++) counter[i] = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < size; j++) {
			if (i == tab[j]) counter[i]++;
		}
	}
	for (int i = 1; i < m; i++) counter[i] = counter[i] + counter[i - 1];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < size; j++) {
			if (i == tab[j]) {
				counter[i]--;
				new_tab[counter[i]] = tab[j];
			}
		}
	}
	for (int i = 0; i < size; i++) {
		tab[i] = new_tab[i];
		cout << tab[i] << ", ";
	}
}
int max(int* tab, int size) {
	int max = 0;
	for (int i = 0; i < size; i++) {
		if (max < tab[i])max = tab[i];
	}
	return max;
}
int min(int* tab, int size) {
	int min = 0;
	for (int i = 0; i < size; i++) {
		if (min > tab[i])min = tab[i];
	}
	return min;
}
int key_value(string s, int N) {

	int sum = 0;

	for (int i = 0; i < s.length(); i++) {
		sum = sum + (int(s[i]) * 2 ^ (s.length() - (i + 1)));
	}
	return sum;
}
void bucket_sort(int* tab, int size) {
	for (int i = 0; i < size; i++) {
		if (tab[i] < 0) {
			cout << "niezgodnosc z dziedzina,\n element w tablicy powinny byc wieksze lub rowne 0" << endl;
			return;
		}
	}
	int k = 0;
	int m = max(tab, size);
	int* new_tab = new int[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j && tab[i] == tab[j]) k++;
		}
	}
	if (k != 0) k = size - k;
	else k = 1;

	for (int p = 1; m / p > 0; p *= 10) {
		int counter[10] = { 0 };

		for (int i = 0; i < size; i++) ++counter[(tab[i] / p) % 10];

		for (int i = 1; i <= 9; i++) counter[i] = counter[i] + counter[i - 1];
		
		for (int i = size-1; i >= 0; i--) new_tab[--counter[(tab[i] / p) % 10]] = tab[i];

		for (int i = 0; i < size; i++) tab[i] = new_tab[i];
	}
	for (int i = 0; i < size; i++) {
		cout << tab[i] << ", ";
	}
	
}
template<typename T>
void bucket_sort(T* tab, int size) {
	int* int_tab = new int[size];
	for (int i = 0; i < size; i++) {
		int_tab[i] = key_value(tab[i], size);
	}
	bucket_sort(int_tab, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (int_tab[i] == key_value(tab[j], size)) {
				cout << tab[j] << ", ";
				break;
			}
		}
	}
}

int main() {

	string stab[10] = {"d", "a", "z", "d", "c", "b", "a", "k", "y", "f"};
	int tab[10] = { 4, 0, 67, 10, 1, 2, 8, 11, 22, 423 };
	//count_sort(tab, 10,(max(tab,10)-min(tab, 10)) );
	//heap_sort();
	bucket_sort(tab, 10);
	bucket_sort(stab, 10);
	return 0;
}