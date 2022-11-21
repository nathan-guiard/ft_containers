#define	DEBUG

#include "set.hpp"
#include "pair.hpp"
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
	std::vector<std::string>			vector;

	vector.push_back("a");
	vector.push_back("b");
	vector.push_back("c");
	vector.push_back("d");
	vector.push_back("e");
	vector.push_back("f");
	vector.push_back("g");

	std::vector<std::string>::iterator	it = vector.begin();
	std::vector<std::string>::iterator	ite = vector.end();


	for (;it != ite; it++)
		std::cout << *it << std::endl;

	std::list<std::string>	l;


	std::list<std::string>::iterator	lit = l.begin();
	std::list<std::string>::iterator	lite = l.end();

	vector.insert(ite, lit, lite);

	ite = vector.end();

	for (; it != ite; it++)
		std::cout << *it << std::endl;
}
