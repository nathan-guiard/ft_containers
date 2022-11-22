#define	DEBUG

#include "utils"
#include "set.hpp"
#include "map.hpp"
#include "vector.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>
#include <list>

int main()
{
	std::vector<int>	v;

	// v.push_back(1);
	// v.push_back(2);

	// v.insert(v.end(), 5, 10);

	std::vector<int>::reverse_iterator			it = v.rbegin();
	std::vector<int>::const_reverse_iterator	ite = v.rend();

	// ft::map<int, int>::reverse_iterator	a(it);
	// ft::map<int, int>::reverse_iterator	b(ite);

	// (void)a;
	// (void)b;
	for (;it != ite; it++)
	{
		std::cout << *it << std::endl;
	}

}
