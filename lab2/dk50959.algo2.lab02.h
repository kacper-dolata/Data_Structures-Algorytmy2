// ALGO2 IS1 212B LAB02
// Kacper Dolata
// dk50959@zut.edu.pl

#pragma once
#include <iostream>
#include <string>

using namespace std;

template<typename T>
class dynamic_array
{
	size_t size;
	size_t capacity;
	T* array;

public:
	dynamic_array()
	{
		size = 0;
		capacity = 1;
		array = new T[capacity];
	}
	void add_end(T value)
	{
		if (capacity == size)
		{
			capacity *= 2;
			T* new_array = new T[capacity];

			for (int i = 0; i < size; i++)
			{
				new_array[i] = array[i];
			}
			delete[] array;
			array = new_array;
		}

		array[size] = value;
		size++;
	}
	void display_index(int index)
	{
		if (size == 0)
		{
			cout << "array is empty" << endl;
			return;
		}
		if (index<0 || index>size - 1)
		{
			cout << "out range" << endl;
			return;
		}
		cout << "value nr " << index << ": " << array[index] << endl;
		cout << "\ncapacity: " << capacity << "\nsize: " << size << endl;
	}
	void change_on_index(T value, int index)
	{
		if (size == 0)
		{
			cout << "array is empty" << endl;
			return;
		}
		if (index<0 || index>size - 1)
		{
			cout << "out range" << endl;
			return;
		}
		cout << "value: " << array[index] << endl;
		array[index] = value;
		cout << "changed value: " << array[index] << endl;
	}
	void clear_array()
	{
		if (size == 0)
		{
			cout << "array is empty" << endl;
			return;
		}

		delete[] array;
		array = nullptr;
		size = 0;
		capacity = 1;
		cout << "array is deleted" << endl;
	}
	void display_array()
	{
		if (size == 0)
		{
			cout << "array is empty" << endl;
			return;
		}
		for (int i = 0; i < size; i++)cout << "value nr " << i << ": " << array[i] << endl;
		cout << "\ncapacity: " << capacity << "\nsize: " << size << endl;
	}
	void sort_array(int choice)
	{
		if (size == 0)
		{
			cout << "array is empty" << endl;
			return;
		}

		if(choice == 0)//od najmniejszej
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 1; j < size - i; j++)
				{
					if (array[j - 1] > array[j])
					{
						swap(array[j - 1], array[j]);
					}
				}
			}
		}
		else if (choice == 1)//od najwiekszej
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 1; j < size - i; j++)
				{
					if (array[j - 1] < array[j])
					{
						swap(array[j - 1], array[j]);
					}
				}
			}
		}
		else
		{
			cout << "wrong choice" << endl;
		}
	}
};