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

template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << *first << " " << *second << std::endl;
	std::cout << "<  :" << (first < second) << std::endl;
	std::cout << "<= :" << (first <= second) << std::endl;
	std::cout << ">  :" << (first > second) << std::endl;
	std::cout << ">= :" << (first >= second) << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<int> vct(size);
	TESTED_NAMESPACE::vector<int>::reverse_iterator it_0(vct.rbegin());
	TESTED_NAMESPACE::vector<int>::reverse_iterator it_1(vct.rend());
	TESTED_NAMESPACE::vector<int>::reverse_iterator it_mid;

	TESTED_NAMESPACE::vector<int>::const_reverse_iterator cit_0 = vct.rbegin();
	TESTED_NAMESPACE::vector<int>::const_reverse_iterator cit_1;
	TESTED_NAMESPACE::vector<int>::const_reverse_iterator cit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	it_0 = vct.rbegin();
	cit_1 = vct.rend();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	std::cout << std::boolalpha;
	std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

	std::cout << "\t\tft_eq_ope:" << std::endl;
	// regular it
	ft_eq_ope(it_0 + 3, it_mid);
	ft_eq_ope(it_0, it_1);
	ft_eq_ope(it_1 - 3, it_mid);
	// const it
	ft_eq_ope(cit_0 + 3, cit_mid);
	ft_eq_ope(cit_0, cit_1);
	ft_eq_ope(cit_1 - 3, cit_mid);
	// both it
	ft_eq_ope(it_0 + 3, cit_mid);
	ft_eq_ope(it_mid, cit_0 + 3);
	ft_eq_ope(it_0, cit_1);
	ft_eq_ope(it_1, cit_0);
	ft_eq_ope(it_1 - 3, cit_mid);
	ft_eq_ope(it_mid, cit_1 - 3);

	return (0);
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


