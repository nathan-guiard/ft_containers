#define	CAN_USE_PRINT 0
#define	DEBUG

#include "rb_tree.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

int main()
{
	tree<int>	t;

	t.add(10);
	t.add(25);
	t.add(50);
	t.add(6);
	t.add(7);
	t.add(78);
	t.add(42);
	t.add(100);
	t.add(12);
	t.add(20);
	t.add(24);
	t.add(88);
	t.add(26);

	t.print();

	// t.del(10);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(25);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(50);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(6);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(7);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(78);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(42);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(100);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(12);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(20);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(24);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(88);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// t.del(26);
	// std::cout << "deleted" << std::endl;
	// t.print();
	// std::cout << "DELETING" << std::endl;
	// t.del(7);
	// t.print();
}