#define	CAN_USE_PRINT 0
#define	DEBUG

#include "set.hpp"
#include "pair.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

typedef ft::set<std::string>::iterator iterator;
typedef ft::set<std::string>::const_iterator const_iterator;
typedef ft::set<std::string>::reverse_iterator reverse_iterator;
typedef ft::set<std::string>::const_reverse_iterator const_reverse_iterator;

// template<class T>
// void	every_comp(const T &a, const T &b, bool s);

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

	std::vector<int>::iterator vit	= v.begin();
	std::vector<int>::iterator vite	= v.end();

	ft::set<int>	ft(vit, vite);
	std::set<int>	std(vit, vite);

	ft._t.print();
	std::cout << "----------------------" << std::endl;
	// TESTS:

	std::cout << *std.lower_bound(45) << " " << *std.upper_bound(80) << std::endl;
	std::cout << *std.lower_bound(50) << " " << *std.upper_bound(90) << std::endl;

}

// template<class T>
// void	every_comp(const T &a, const T &b, bool s)
// {
// 	std::cout << (s ? "\033[32mFT" : "\033[34mSTD") << std::endl;
// 	std::cout << "eq: " << (a == b) << " | ";
// 	std::cout << "ne: " << (a != b) << std::endl;
// 	std::cout << "lt: " << (a < b) << " | ";
// 	std::cout << "le: " << (a <= b) << std::endl;
// 	std::cout << "gt: " << (a > b) << " | ";
// 	std::cout << "ge: " << (a >= b) << std::endl;
// 	std::cout << "\033[0m";
// }