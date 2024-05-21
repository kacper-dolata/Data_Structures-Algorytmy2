//ALGO2 IS1 212B LAB09
//Kacper Dolata
//dk50959@zut.edu.pl
#include <iostream>
#include <fstream>
#include "lista.h"

using namespace std;

class Point {
	double x,y;
public:
	Point() :x{ 0 }, y{ 0 } {}
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	double get_x() {
		return x;
	}
	double get_y() {
		return y;
	}
	void setter(double x, double y) {
		this->x = x;
		this->y = y;
	}
	bool operator!=(Point& right) {
		if (this->x != right.x || this->y != right.y) {
			return true;
		}
		return false;
	}
};
ostream& operator<<(ostream& out, Point& point)
{
	return out << '<' << point.get_x() << ',' << point.get_y() << '>';
}
class Plot {
	int num_of_points;
	Point** tab_points;
public:
	Plot(string str){
		fstream plik;
		double x = 0, y = 0;
		plik.open(str, ios::in);

		if (plik.good()) {
			plik >> num_of_points;
			tab_points = new Point * [num_of_points];
			for (int i = 0; i < num_of_points; i++) {
				plik >> x >> y;
				Point* point = new Point(x, y);
				tab_points[i] = point;
			}
			plik.close();
		}
		else cout << "can't open file";
	}
	int get_num_of_points() {
		return num_of_points;
	}
	Point** get_tab() {
		return tab_points;
	}
};
double det_f(Point P1, Point P2) {
	return (P1.get_x() * P2.get_y()) - (P2.get_x() * P1.get_y());
}
void sort(Point** tab, int n) {
	Point tmp_p1(0, 0), tmp_p2(0, 0);
	double det = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n-1; j++) {
			tmp_p1.setter((tab[j]->get_x() - tab[0]->get_x()), (tab[j]->get_y() - tab[0]->get_y()));
			tmp_p2.setter((tab[j+1]->get_x() - tab[0]->get_x()), (tab[j+1]->get_y() - tab[0]->get_y()));
			det = det_f(tmp_p1, tmp_p2);
			if (det < 0) {
				swap(tab[j], tab[j + 1]);
			}
		}
	}
}
Linked_list<Point>* graham(Point** tab_points, int num_of_points) {
	Point tmp_p1(0, 0), tmp_p2(0, 0);
	double ymin = tab_points[0]->get_y(), det = 0;
	int min = 0;
	for (int i = 0; i < num_of_points; i++) {
		if (tab_points[i]->get_y() < ymin || (tab_points[i]->get_y() == ymin && tab_points[i]->get_x() < tab_points[min]->get_x())) {
			ymin = tab_points[i]->get_y();
			min = i;
		}
	}
	
	swap(tab_points[0], tab_points[min]);
	sort(tab_points, num_of_points);

	Linked_list<Point>* lista = new Linked_list<Point>();
	lista->add_end(*tab_points[0]);
	lista->add_end(*tab_points[1]);
	Point *A = tab_points[1], *B = tab_points[0];

	for (int i = 2; i < num_of_points; i++) {
		
		tmp_p1.setter((A->get_x() - B->get_x()), (A->get_y() - B->get_y()));
		tmp_p2.setter((tab_points[i]->get_x() - B->get_x()), (tab_points[i]->get_y() - B->get_y()));

		if (det_f(tmp_p1, tmp_p2) <= 0) {
			int j = 1;
			while (det_f(tmp_p1, tmp_p2) <= 0) {
				lista->search_remove(*tab_points[i - j]);
				A = lista->search_index(lista->size_list() - 1);
				B = lista->search_index(lista->size_list() - 2);
				tmp_p1.setter((A->get_x() - B->get_x()), (A->get_y() - B->get_y()));
				tmp_p2.setter((tab_points[i]->get_x() - B->get_x()), (tab_points[i]->get_y() - B->get_y()));
				j++;
			}
		}
		
		lista->add_end(*tab_points[i]);
		A = lista->search_index(lista->size_list() - 1);
		B = lista->search_index(lista->size_list() - 2);
	}

	return lista;
}

int main() {
	Plot* plot = new Plot("points1.txt");
	Linked_list<Point>* otoczka = graham(plot->get_tab(), plot->get_num_of_points());
	otoczka->display_all();

	return 0;
}