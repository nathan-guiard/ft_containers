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
	ft::map<char, int>			std;

	std.at('y');
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