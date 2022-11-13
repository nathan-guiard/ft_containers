#define	CAN_USE_PRINT 0
#define	DEBUG

#include "set.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

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

	std::vector<std::string>::iterator vit = v.begin();
	std::vector<std::string>::iterator vite = v.end();

	ft::set<std::string>	s(vit, vite);

	s._t.print();
	std::cout << "----------------------" << std::endl;

}