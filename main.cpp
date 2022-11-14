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

typedef std::set<std::string>::iterator std_iterator;
typedef std::set<std::string>::const_iterator std_const_iterator;
typedef std::set<std::string>::reverse_iterator std_reverse_iterator;
typedef std::set<std::string>::const_reverse_iterator std_const_reverse_iterator;


template<class T>
void        every_comp(const T &a, const T &b, bool s);

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

	ft::set<std::string>	s(vit, vite);
	std::set<std::string>	o(vit, vite);

	// s._t.print();
	std::cout << "----------------------" << std::endl;
	// TESTS:

	iterator	it = s.lower_bound("b");
	std_iterator	sit = o.lower_bound("b");

	std::cout << *it << " " << *sit;
}

template<class T>
void        every_comp(const T &a, const T &b, bool s)
{
	std::string color = (s ? "\033[35m" : "\033[34m");

	std::cout << color << (s ? "FT" : "STD") << std::endl;
    std::cout << "==: " << ((a == b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << " | ";
    std::cout << "!=: " << ((a != b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << std::endl;
    std::cout << "< : " << ((a <  b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << " | ";
    std::cout << "<=: " << ((a <= b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << std::endl;
    std::cout << "> : " << ((a >  b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << " | ";
    std::cout << ">=: " << ((a >= b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << std::endl;
    std::cout << "\033[0m";
}