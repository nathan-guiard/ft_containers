/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:20 by nguiard           #+#    #+#             */
/*   Updated: 2022/10/29 11:01:32 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "node.hpp"
#include <iostream>
#include <unistd.h>
#include <iomanip>

template <typename T>
class	tree
{
private:

public:
	tree() {
		root = 0;
		size = 0;
	}
	tree(const T &v) {
		root = new node<T>(v);
		size = 0;
	}
	tree (const tree &copy){
		root = copy.root; // NOT DEEP COPY, CHANGE WHEN ITERATION WORKS
		size = copy.size;
	}
	~tree() {};

	void	add(const T &val)
	{
		node<T>	*p = root;
		node<T>	*nv = new node<T>(val);

		if (search(val) == true)
		{
			std::cerr << "Duplicate detected." << std::endl;
			delete nv;
			return;
		}
		if (root)
		{
			while (1)
			{
				if (val > p->value && !p->right)
					break;
				if (val < p->value && !p->left)
					break;
				if (val > p->value)
					p = p->right;
				else
					p = p->left;
			}
		}
		_insert(p, nv);
		size++;
	}

	bool	search(const T &val) //needs to return iterators
	{
		node<T>	*searching = root;
		if (root == 0)
			return false;
		while (1)
		{
			if (!searching)
				return false;
			if (searching->value == val)
				return true;
			if (searching->value > val)
				searching = searching->left;
			else
				searching = searching->right;
		}
	}

	#ifdef CAN_USE_PRINT
	void	print()
	{
		real_print(root, 0);
	}

	void	real_print(node<T> *ptr, int space)
	{
		if (!ptr)
			return;
		space += 4;
		real_print(ptr->right, space);
		for (int i = 4; i < space; i++)
			std::cout << " ";
		std::cout << (ptr->color == black ? "\033[90m" : "\033[31m") << std::setw(4) << ptr->value << "\033[0m" << std::endl;
		real_print(ptr->left, space);
	}
	#endif

//private
	node<T>			*root;
	unsigned int	size;

	void	_insert(node<T> *parent, node<T> *child)
	{
		if (!parent) // case 0: new root
		{
			root = child;
			child->color = black;
			return ;
		}
		_add_simple_node(parent, child);
		if (parent->parent && parent->borther()
			&& parent->borther()->color == red) // case 1 : red uncle
			red_uncle(parent);
		else if ((parent->parent && parent->borther()
			&& parent->borther()->color == black))
		{
			if ((parent->parent->right == parent && parent->value < child->value)
				|| (parent->parent->left == parent && parent->value > child->value)) //case 3 -> uncle black line
				black_line(parent, child);
			else	// case 2 -> black uncle triangle
				black_triangle(parent, child);
		}
	}

	void	_add_simple_node(node<T> *p, node<T> *n)
	{
		if (!p)
			return;
		if (p->value > n->value)
		{
			p->left = n;
			n->parent = p;
		}
		else
		{
			p->right = n;
			n->parent = p;
		}
	}

	// Solution -> recolor childs parent, GP and uncle
	void	red_uncle(node<T> *parent)
	{
		parent->color *= -1;
		parent->parent->color *= -1;
		parent->borther()->color *= -1;
	}

	// Rotate parent in the opposite direction of child
	void	black_triangle(node<T> *parent, node<T> *child)
	{
		if (parent->left == child)
			right_rotation(parent);
		else
			left_rotation(parent);
	}

	//	Rotate GP in opposite direction of child 
	//	and recolor original parent and GP of child.
	void	black_line(node<T> *parent, node<T> *child)
	{
		node<T>	*GP = parent->parent;

		std::cout << "Black line Child = " << child->value << " parent = " << parent->value << std::endl;
		if (parent->left == child)
			right_rotation(GP);
		else
			left_rotation(GP);
		parent->color *= -1;
		GP->color *= -1;
	}

	void	left_rotation(node<T> *GP)
	{
		node<T>	*P;
		node<T>	*Z;
		node<T>	*save;

		std::cout << GP->value << "is the GP of LR" << std::endl;
		if (!GP)
			return;
		save = GP->parent;
		P = GP->right;
		if (!P)
			return;
		Z = P->left;
		if (!Z)
			_add_simple_node(P, GP);
		else
		{	
			_add_simple_node(GP, Z);
			_add_simple_node(P, GP);
		}
		_add_simple_node(save, P);
	}

	void	right_rotation(node<T> *GP)
	{
		node<T>	*P;
		node<T>	*Z;
		node<T>	*save;

		std::cout << GP->value << " is the GP of RR" << std::endl;
		if (!GP)
			return;
		save = GP->parent;
		P = GP->left;
		if (!P)
			return;
		Z = P->right;
		if (!Z)
		{
			_add_simple_node(P, GP);
			std::cout << GP->value << " ajoute en child de " << P->value << std::endl;
			std::cout << "GP left " << GP->left->value << " P right " << P->right->value << std::endl;
			GP->left = 0;
		}
		else
		{	
			_add_simple_node(GP, Z);
			std::cout << Z->value << " ajoute a gauche de " << GP->value << std::endl;
			_add_simple_node(P, GP);
			std::cout << GP->value << " ajoute a droite de " << P->value << std::endl;
		}
		if (save)
			_add_simple_node(save, P);
		else
		{
			save = root->right;
			root = P;
			_add_simple_node(P->right, save);
		}
		std::cout << P->value << " ajoute en child de " << (save == 0 ? 0 : save->value) << std::endl;
		getwchar();
	}

};

#endif