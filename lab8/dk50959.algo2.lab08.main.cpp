//ALGO2 IS1 212B LAB08
//Kacper Dolata
//dk50959@zut.edu.pl
#include <iostream>
#include <fstream>

using namespace std;

class Node {
	int id;
	float x;
	float y;
public:
	Node() {
		id = 0;
		x = 0;
		y = 0;
	}
	Node(int id, float x, float y) {
		this->id = id;
		this->x = x;
		this->y = y;
	}
	int get_id() {
		return id;
	}
	float get_x() {
		return x;
	}
	float get_y() {
		return y;
	}
};
class Edge {
	int id_1;
	int id_2;
	float cost;
public:
	Edge() {
		id_1 = 0;
		id_2 = 0;
		cost = 0;
	}
	Edge(int id_1,int id_2,float cost) {
		this->id_1 = id_1;
		this->id_2 = id_2;
		this->cost = cost;
	}
	int get_id_1() {
		return id_1;
	}
	int get_id_2() {
		return id_2;
	}
	float get_cost() {
		return cost;
	}
};
class Graph {
	int num_of_node;
	int num_of_edge;
	Node** tab_node;
	Edge** tab_edge;

public:
	Graph(string str) {
		fstream plik;
		float x = 0, y = 0, cost = 0;
		int id1 = 0, id2 = 0;
		plik.open(str, ios::in);
		if (plik.good()) {
			plik >> num_of_node;
			tab_node = new Node * [num_of_node];
			for (int i = 0; i < num_of_node; i++) {
				plik >> x >> y;
				Node* node = new Node(i, x, y);
				tab_node[i] = node;
			}
			plik >> num_of_edge;
			tab_edge = new Edge * [num_of_edge];
			for (int i = 0; i < num_of_edge; i++) {
				plik >> id1 >> id2 >> cost;
				Edge* edge = new Edge(id1, id2, cost);
				tab_edge[i] = edge;
			}
			plik.close();
		}
		else cout << "can't open file";
	}
	int getNumofNodes() {
		return num_of_node;
	}
	int getNumofEdges() {
		return num_of_edge;
	}
	Edge** gettab() {
		return tab_edge;
	}
};
class Union_Find {
	int* parent;
public:
	Union_Find(int num_of_nodes){
		parent = new int[num_of_nodes];
		for (int i = 0; i < num_of_nodes; i++) {
			parent[i] = i;
		}
	}
	int find(int i) {
		if (parent[i] == i) return i;
		return find(parent[i]);
	}
	void union_nodes(int x,int y) {
		int parent_x = find(x) , parent_y = find(y);
		if (parent_x != parent_y) parent[parent_y] = parent_x;
	}
};

void sort(Edge** tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (tab[j]->get_cost() > tab[j + 1]->get_cost())
				swap(tab[j], tab[j + 1]);

		}
	}
}
int partition(Edge** tab, int start, int end)
{

	float pivot = tab[start]->get_cost();

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (tab[i]->get_cost() <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	swap(tab[pivotIndex], tab[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (tab[i]->get_cost() <= pivot) {
			i++;
		}

		while (tab[j]->get_cost() > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(tab[i++], tab[j--]);
		}
	}

	return pivotIndex;
}
void quickSort(Edge** tab, int start, int end)
{

	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(tab, start, end);

	// Sorting the left part
	quickSort(tab, start, p - 1);

	// Sorting the right part
	quickSort(tab, p + 1, end);
}

Edge** kruskal(Graph* graph) {

	Edge** tab_edge = graph->gettab();
	Edge** MST_tab = new Edge * [graph->getNumofNodes() - 1]();

	Union_Find* uf = new Union_Find(graph->getNumofNodes());
	//sort(tab_edge, graph->getNumofEdges());
	quickSort(tab_edge, 0, graph->getNumofEdges() - 1);
	float m_cost = 0;
	int j = 0;

	for (int i = 0; i < graph->getNumofEdges(); i++) {

		if (uf->find(tab_edge[i]->get_id_1()) != uf->find(tab_edge[i]->get_id_2())) {
			uf->union_nodes(tab_edge[i]->get_id_1(), tab_edge[i]->get_id_2());
			m_cost += tab_edge[i]->get_cost();
			MST_tab[j] = new Edge(tab_edge[i]->get_id_1(), tab_edge[i]->get_id_2(), tab_edge[i]->get_cost());
			j++;
		}
	}
	cout << "Min cost: " << m_cost << "\nNum of edges: " << j << endl;

	return MST_tab;
}

int main() {

	Graph* graph = new Graph("g3.txt");
	
	Edge** tab = kruskal(graph);
	cout << "=============== Edges of MST ===============\n\n";
	for (int i = 0; i < 20; i++) {
		if (i == graph->getNumofNodes()-1) break;
		cout << tab[i]->get_id_1() << " - " << tab[i]->get_id_2() << " cost: " << tab[i]->get_cost() << endl;
	}

	return 0;
}