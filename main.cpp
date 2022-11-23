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

template<class T>
void        every_comp(const T &a, const T &b, bool s);

#define TESTED_NAMESPACE ft

int		main(void)
{
	ft::map<int, char>	m;

	m.insert(ft::pair<const int, char>(9, '7'));
	m.insert(ft::pair<const int, char>(9, '7'));
	m.insert(ft::pair<const int, char>(9, '7'));
}



// template<class T>
// void        every_comp(const T &a, const T &b, bool s)
// {
// 	std::string color = (s ? "\033[35m" : "\033[34m");
// 	std::cout << color << (s ? "FT" : "STD") << std::endl;
//     std::cout << "==: " << ((a == b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << " | ";
//     std::cout << "!=: " << ((a != b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << std::endl;
//     std::cout << "< : " << ((a <  b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << " | ";
//     std::cout << "<=: " << ((a <= b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << std::endl;
//     std::cout << "> : " << ((a >  b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << " | ";
//     std::cout << ">=: " << ((a >= b) ? "\033[1;32mtrue " : "\033[1;31mfalse") << color << std::endl;
//     std::cout << "\033[0m";
// }


