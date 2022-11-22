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
	ft::vector<int>	v;

	v.push_back(1);
	v.push_back(2);

	v.insert(v.end(), 5, 10);

	ft::vector<int>::iterator	it = v.begin();
	ft::vector<int>::iterator	ite = v.end();

	for (;it != ite; it++)
	{
		std::cout << *it << std::endl;
	}

	v.erase(++v.begin(), v.end());

	std::cout << "---" << std::endl;
	it = v.begin();
	ite = v.end();

	for (;it != ite; it++)
	{
		std::cout << *it << std::endl;
	}
}
