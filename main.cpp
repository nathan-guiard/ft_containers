#define	CAN_USE_PRINT 0
#define	DEBUG

#include "rb_tree.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

int main()
{
	ft::tree<int>	t;

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

	t.del(10);
	std::cout << "deleted 10" << std::endl;
	t.print();
	t.del(25);
	std::cout << "deleted 25" << std::endl;
	t.print();
	t.del(50);
	std::cout << "deleted 50" << std::endl;
	t.print();
	t.del(6);
	std::cout << "deleted 6" << std::endl;
	t.print();
	t.del(7);
	std::cout << "deleted 7" << std::endl;
	t.print();
	t.del(78);
	std::cout << "deleted 78" << std::endl;
	t.print();
	t.del(42);
	std::cout << "deleted 42" << std::endl;
	t.print();
	t.del(100);
	std::cout << "deleted 100" << std::endl;
	t.print();
	t.del(12);
	std::cout << "deleted 12" << std::endl;
	t.print();
	t.del(20);
	std::cout << "deleted 20" << std::endl;
	t.print();
	t.del(24);
	std::cout << "deleted 24" << std::endl;
	t.print();
	t.del(88);
	std::cout << "deleted 88" << std::endl;
	t.print();
	t.del(26);
	std::cout << "deleted 26" << std::endl;
	t.print();
}