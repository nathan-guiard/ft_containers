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
	std::vector<int>	v(13);

	for (int i = 0; i < 42; i++)
	{
		std::cout << v.size() << ": " << v.capacity() << std::endl;
		v.push_back(42);
	}

	std::vector<int>::iterator	it = v.begin();
	std::vector<int>::iterator	ite = v.end();

	std::cout << "--------------------" <<std::endl;
	for (; it != ite; it++)
		std::cout << *it << std::endl;
	std::cout << "--------------------" <<std::endl;

	for (; v.size() > 0;)
	{
		std::cout << v.size() << ": " << v.capacity() << std::endl;
		v.pop_back();
	}
}
