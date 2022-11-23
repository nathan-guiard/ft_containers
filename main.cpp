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

int main()
{
	ft::vector<int>	v(5);

	ft::vector<int>::reverse_iterator		it = v.rbegin();
	ft::vector<int>::const_reverse_iterator	ite = v.rbegin();

	for (int i = 0; i < 5; ++i)
	{
		it[i] = (5 - i);
		std::cout << it[i] << std::endl;
	}
	std::cout << std::endl;

	it = it + 5; std::cout << "(it = it + 5): " << *it << std::endl;
	it = 1 + it; std::cout << "(it = 1 + it): " << *it << std::endl;
	it = it - 4; std::cout << "(it = it - 4): " << *it << std::endl;
	std::cout << *it << std::endl;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

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
