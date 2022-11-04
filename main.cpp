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
	v.push_back(2);

	std::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator ite = v.end();

	ft::set<int>	s(it, ite);
	// s._t.print();

	ft::tree<int>	a;

	a.add(5);
	a.add(10);
	a.add(4);
	a.add(12);
	a.add(6);
}