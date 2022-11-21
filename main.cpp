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

template <bool, typename T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };

template <class T>
struct is_int { static const bool test = false;};

template <>
struct is_int<int> { static const bool test = true;};

// template <bool status>

// typedef	bool_type<true>		true_type;
// typedef	bool_type<false>	false_type;

void	fnc(int a)
{
	(void)a;
	std::cout << "C'est un int!" << std::endl;
}

template <class T>
void	fnc(T a, typename enable_if<!is_int<T>::test, T>::type * = NULL)
{
	(void)a;
	std::cout << "C'est pas un int!" << std::endl;
}

int main()
{
	std::vector<int>	v(13);

	for (int i = 0; i < 42; i++)
	{
		std::cout << v.size() << ": " << v.capacity() << std::endl;
		v.push_back(42);
	}

	std::vector<int>::iterator	it = v.begin();
	std::vector<int>::iterator	ite = v.end();

	std::cout << "--------------------" <<std::endl;
	for (; it != ite; it++)
		std::cout << *it << std::endl;
	std::cout << "--------------------" <<std::endl;

	for (; v.size() > 0;)
	{
		std::cout << v.size() << ": " << v.capacity() << std::endl;
		v.pop_back();
	}
	it = v.begin();
	ite = v.end();

	ft::vector<int>	test(it, ite);
	ft::vector<int>	test2(7, 42);

	fnc(7);
	fnc("hello");
}
