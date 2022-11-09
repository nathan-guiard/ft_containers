#define	CAN_USE_PRINT 0
#define	DEBUG

#include "set.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

int main()
{
	std::vector<int>	v;

	v.push_back(5);
	v.push_back(10);
	v.push_back(4);
	v.push_back(9);
	v.push_back(25);
	v.push_back(26);
	v.push_back(98);
	v.push_back(120);
	v.push_back(8);
	v.push_back(22);
	v.push_back(20);
	v.push_back(90);
	v.push_back(50);
	v.push_back(72);
	v.push_back(42);
	v.push_back(609);

	std::vector<int>::iterator vit = v.begin();
	std::vector<int>::iterator vite = v.end();

	ft::set<int>	s(vit, vite);
	ft::set<int>	sb(vit, vite);

	s._t.print();
	std::cout << "----------------------" << std::endl;

	std::cout << (s == sb) << std::endl;
	std::cout << (s != sb) << std::endl;
	sb.insert(842);
	// std::cout
	// ft::set<int>::iterator	it = s.begin();

}