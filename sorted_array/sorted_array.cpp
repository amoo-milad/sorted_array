// sorted_array.cpp : two arrays; one sorted and one unsorted

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <time.h>
//#include <stdio.h>
//#include <stdlib.h>

const int N = 10;

class Array {
protected:
	int* data; /// instead of  int data[N];
	int size;
	bool is_sorted = false;

public:
	Array(int number = N) {  // constructor
		size = number;
		data = new int[number];
	}

	Array(const Array& a) {  // copy constructor
		data = NULL;
		*this = a;

		//size = a.size;
		//is_sorted = a.is_sorted;
		//data = new int[a.size];
		//for (int i = 0; i < a.size; i++)
		//	data[i] = a.data[i];
	}

	Array& operator=(const Array& a) {  // assignment operator
		if (this == &a)
			return *this;

		if (data != NULL)
			delete[] data;

		size = a.size;
		is_sorted = a.is_sorted;
		data = new int[a.size];
		for (int i = 0; i < a.size; i++)
			data[i] = a.data[i];
		return *this;
	}

	~Array() {  // destructor
		delete[] data;
	}

	int count() const {
		return size;
	}

	virtual int& operator[](int index) {
		if (index < 0 || index >= size)
		{
			throw std::exception("There is no array_member with such an index!\n ");
		}

		return data[index];
	}

	bool set(int index, int value) {

		data[index] = value;
		is_sorted = false;
		return true;
	}

	int get(int index) const {

		if (index < 0 || index >= size)
		{
			throw std::exception("There is no array_member with such an index!\n ");
		}

		return data[index];
	}

	void fill_random() {

		srand(time(NULL));
		for (int i = 0; i < size; i++)
			data[i] = (int)((long long)rand() * 1000000 / RAND_MAX);

		is_sorted = false;
	}

	void display() const
	{
		for (int i = 0; i<size; i++)
			printf("\n%3d: %6d", i, data[i]);
	}

	void sort()
	{
		if (is_sorted)
			return;

		for (int j = N - 1; j>0; j--)
			for (int i = 0; i<j; i++)
				if (data[i] > data[i + 1])
				{
					int temp = data[i];
					data[i] = data[i + 1];
					data[i + 1] = temp;
				}
		is_sorted = true;
	}

	virtual int search(int number) const // linear search
	{
		int index = -1;

		for (int i = 0; i<size; i++)
			if (data[i] == number)
			{
				index = i;
				break;
			}
		return index;
	}
};

class SortedArray : public Array {
private:
	int binary_search(int number, int down, int top)
	{
		sort();

		int mid = (down + top) / 2;

		if (number == data[mid])
			return mid;

		if (down == top)
			return -1; // not found! End condition.

		if (number < data[mid])
			return binary_search(number, down, mid);

		//if(number > Array[mid])
		return binary_search(number, mid + 1, top);
	}

public:
	virtual bool set(int index, int value) {

		if (index < 0 || index >= size)
			throw std::exception("There is no array_member with such an index!");

		Array::set(index, value);
		sort();
		return true;
	}

	virtual int search(int number)  // Binary search
	{
		return binary_search(number, 0, size - 1);
	}

};

int main()
{
	SortedArray b;
	Array& a = b;
	a.fill_random();

	int n = a[9];
	a[9] = 666;

	for (int i = 0; i < a.count(); i++)
		a[i] = i * 2;

	while (true)
	{
		int x;
		printf("\n\nplease enter a number, each will do the specified job:\n\n ");
		printf("1=> Fill the array with random numbers\n ");
		printf("2=> Display the array\n ");
		printf("3=> Search the array\n ");
		printf("4=> Set a member of the array\n ");
		printf("5=> Get a member of the array\n ");
		printf("6=> Sort the array\n ");

		printf("\n 7=> Search the array\n ");
		printf("8=> Set a member of the array\n ");

		printf("0=> Exit\n\n\n ");
		scanf("%d", &x);

		using namespace std;
		try {

			switch (x)
			{
			case 1:
				a.fill_random();
				break;   /////////////////////////////////////////////////////////////////////////			

			case 2:
				a.display();
				break;   /////////////////////////////////////////////////////////////////////////

			case 3:
			{
				int number = -3;
				printf("\nEnter the number you want to find: ");
				scanf("%d", &number);
				int index = a.search(number);

				if (index == -1)
					throw exception("not found in the array");
				else
					printf("\nthe index of '%d' is: %d", number, index);
			}
			break;   /////////////////////////////////////////////////////////////////////////

			case 4:
			{
				int index, value;
				printf_s("please give the index: ");
				scanf("%d", &index);
				printf_s("and the value, please: ");
				scanf("%d", &value);

				a.set(index, value);

				break;   /////////////////////////////////////////////////////////////////////////			
			}

			case 5:
			{
				int index;
				printf_s("please give the index: ");
				scanf("%d", &index);

				int value = a.get(index);
				if (value == -1)
					throw exception("not found in the array");
				else
					printf_s("the value of index %d is: %d \n", index, value);

				break;   /////////////////////////////////////////////////////////////////////////			
			}

			case 6:
				a.sort();
				break;   /////////////////////////////////////////////////////////////////////////	

			case(0):
				//EXIT
				return 0; /////////////////////////////////////////////////////////////////////////



			case 7:	//for sortedArray
			{
				int number = -3;
				printf("\nEnter the number you want to find: ");
				scanf("%d", &number);
				int index = b.search(number);

				if (index == -1)
					throw exception("not found in the array");
				else
					printf("\nthe index of '%d' is: %d", number, index);

				break;   /////////////////////////////////////////////////////////////////////////	
			}

			case 8:	//for sortedArray
			{
				int index, value;
				printf_s("please give the index: ");
				scanf("%d", &index);
				printf_s("and the value, please: ");
				scanf("%d", &value);

				b.set(index, value);

				break;   /////////////////////////////////////////////////////////////////////////			
			}

			default:
				throw exception("Invalid Request!  Try Again...");
				break;	 /////////////////////////////////////////////////////////////////////////
			}

		}
		catch (const exception& e) {
			printf("\n Error: %s \n", e.what());
		}
	}

	system("pause");
	return 0;
}
