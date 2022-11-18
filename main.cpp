// #define	CAN_USE_PRINT 0
#define	DEBUG

#include "set.hpp"
#include "pair.hpp"
#include "map.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>

typedef ft::set<std::string>::iterator iterator;
typedef ft::set<std::string>::const_iterator const_iterator;
typedef ft::set<std::string>::reverse_iterator reverse_iterator;

typedef std::set<std::string>::iterator std_iterator;
typedef std::set<std::string>::const_iterator std_const_iterator;
typedef std::set<std::string>::reverse_iterator std_reverse_iterator;
typedef std::set<std::string>::const_reverse_iterator std_const_reverse_iterator;


template<class T>
void        every_comp(const T &a, const T &b, bool s);

template<class T, class U>
void	cmp(const T &ft, const T &ft2, const U &std, const U &std2);

int main()
{
	ft::map<char, int>			ft;
	// std::map<char, int>			std;
	ft::map<char, int>			ft2;
	// std::map<char, int>			std2(std);

	ft['a'] = 2; ft['b'] = 3; ft['c'] = 4; ft['d'] = 5;
	ft2['a'] = 2; ft2['b'] = 3; ft2['c'] = 4; ft2['d'] = 5;
	// std['a'] = 2; std['b'] = 3; std['c'] = 4; std['d'] = 5;
	// std2['a'] = 2; std2['b'] = 3; std2['c'] = 4; std2['d'] = 5;

	std::cout << "----------------------" << std::endl;
	// TESTS:
	// cmp(ft, ft, std, std);
	// cmp(ft, ft2, std, std2);
	

	// ft['e'] = 6; ft['f'] = 7; ft['h'] = 8; ft['h'] = 9;
	// ft2['e'] = 6; ft2['f'] = 7; ft2['h'] = 8; ft2['h'] = 9;

	every_comp(ft, ft, 1);
	every_comp(ft2, ft2, 1);

	ft2['e'] = 6; ft2['f'] = 7; ft2['h'] = 8; ft2['h'] = 9;

	every_comp(ft, ft2, 1);
	every_comp(ft2, ft, 1);

	(++(++ft.begin()))->second = 42; // ft['c'] = 42 donc ft > ft2

	ft::map<char, int>::iterator	it = ft.begin();
	ft::map<char, int>::iterator	ite = ft.end();

	for (; it != ite; it++)
		std::cout << "ft[" << (*it).first <<"]:  " << (*it).second << std::endl;
	
	ft::map<char, int>::iterator	it2 = ft2.begin();
	ft::map<char, int>::iterator	it2e = ft2.end();

	std::cout << std::endl;

	for (; it2 != it2e; it2++)
		std::cout << "ft2[" << (*it2).first <<"]: " << (*it2).second << std::endl;

	// std::cerr << "ft puis ft2" << std::endl;
	every_comp(ft, ft2, 1);
	// std::cerr << "ft2 puis ft" << std::endl;
	every_comp(ft2, ft, 1);
	// std::cout << "Superieur puis inferieur" << std::endl;
	// cmp(ft, ft2, std, std2);
	// cmp(ft2, ft, std2, std);
	// std::cout << "Bizzaries" << std::endl;
	// (++(++ft.begin()))->second = 42;
	// cmp(ft, ft2, std, std2);
	// cmp(ft2, ft, std2, std);

	// std::cout << "Inferieur pius superieur" << std::endl;
	// ft.swap(ft2);
	// std.swap(std2);
	// cmp(ft, ft2, std, std2);
	// cmp(ft2, ft, std2, std);

}

template<class T, class U>
void	cmp(const T &ft, const T &ft2, const U &std, const U &std2)
{
	every_comp(ft, ft2, 1);
	every_comp(std, std2, 0);
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