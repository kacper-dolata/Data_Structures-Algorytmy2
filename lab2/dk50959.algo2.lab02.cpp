// ALGO2 IS1 212B LAB02
// Kacper Dolata
// dk50959@zut.edu.pl

#include "dk50959.algo2.lab02.h"

using namespace std;

int main() 
{
	dynamic_array<int>* da = new dynamic_array<int>;

	da->add_end(1);
	da->add_end(10);
	da->add_end(5);
	da->add_end(7);
	da->add_end(3);
	da->sort_array(0);
	da->display_array();

	return 0;
}