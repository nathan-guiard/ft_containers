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

template<class T>
void	every_comp(const T &a, const T &b, bool s);

int main()
{
	std::vector<std::string>	v;

	v.push_back("a");
	v.push_back("b");
	v.push_back("c");
	v.push_back("d");
	v.push_back("e");
	v.push_back("f");
	v.push_back("g");
	v.push_back("h");
	v.push_back("i");
	v.push_back("j");
	v.push_back("k");
	v.push_back("l");
	v.push_back("m");
	v.push_back("n");
	v.push_back("o");
	v.push_back("p");

	std::vector<std::string>::iterator vit	= v.begin();
	std::vector<std::string>::iterator vite	= v.end();

	ft::set<std::string>	ft(vit, vite);
	ft::set<std::string>	ft2(ft);
	std::set<std::string>	std(vit, vite);
	std::set<std::string>	std2(std);

	// s._t.print();
	std::cout << "----------------------" << std::endl;
	// TESTS:
	every_comp(ft, ft2, 1);
	every_comp(std, std2, 0);
	every_comp(ft, ft, 1);
	every_comp(std, std, 0);

	std::cout << "GT/GE/NE" << std::endl;
	ft.insert("coucou");
	std.insert("coucou");
	every_comp(ft, ft2, 1);
	every_comp(std, std2, 0);
	std::cout << "a l'envers" << std::endl;
	every_comp(ft2, ft, 1);
	every_comp(std2, std, 0);

	std::cout << "LT/LE/NE" << std::endl;
	ft2.insert("coucou");
	std2.insert("coucou");
	ft2.insert("COUCOU MF");
	std2.insert("COUCOU MF");
	every_comp(ft, ft2, 1);
	every_comp(std, std2, 0);
	std::cout << "a l'envers" << std::endl;
	every_comp(ft2, ft, 1);
	every_comp(std2, std, 0);
}

template<class T>
void	every_comp(const T &a, const T &b, bool s)
{
	std::cout << (s ? "\033[32mFT" : "\033[34mSTD") << std::endl;
	std::cout << "eq: " << (a == b) << " | ";
	std::cout << "ne: " << (a != b) << std::endl;
	std::cout << "lt: " << (a < b) << " | ";
	std::cout << "le: " << (a <= b) << std::endl;
	std::cout << "gt: " << (a > b) << " | ";
	std::cout << "ge: " << (a >= b) << std::endl;
	std::cout << "\033[0m";
}