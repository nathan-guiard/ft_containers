#define	CAN_USE_PRINT 0
#define	DEBUG

#include "rb_tree.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

// void shuffle(int *arr, size_t n)
// {
//     if (n > 1) 
//     {
//         size_t i;
//         for (i = 0; i < n - 1; i++) 
//         {
//           size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
//           int t = arr[j];
//           arr[j] = arr[i];
//           arr[i] = t;
//         }
//     }
// }


int main()
{
	tree<int>	t;

	t.add(10);
	t.add(50);
	t.add(25);
	t.add(54);
	t.add(42);
	t.add(6);

	t.print();
	t.add(4);
	// t.add(2);

	t.print();
}