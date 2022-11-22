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
	std::vector<int>	v(4);
	std::vector<int>	v2(4);

	every_comp(v, v2, 1);
	every_comp(v2, v, 1);

	v2.resize();

	every_comp(v, v2, 1);
	every_comp(v2, v, 1);

	for (;it != ite; it++)
	{
		std::cout << *it << std::endl;
	}

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
