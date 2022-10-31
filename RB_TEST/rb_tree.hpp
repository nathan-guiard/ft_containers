/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:20 by nguiard           #+#    #+#             */
/*   Updated: 2022/10/31 09:24:17 by nguiard          ###   ########.fr       */
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

		if (search(val) != 0)
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
		else
			root = nv;
		_insert(p, nv);
		size++;
	}

	void	del(const T &val)
	{
		node<T>		*to_del = search(val);
		node<T>		*x;
		node<T>		*y;
		int			color;

		if (!val)
		{
			std::cerr << val << " not found." << std::endl;
			return;
		}
		color = to_del->color;
		if (!to_del->left)
		{
			x = to_del->right;
			_transplant(to_del, to_del->right);
		}
		else if (!to_del->right)
		{
			x = to_del->left;
			_transplant(to_del, to_del->left);
		}
		else
		{
			y = _min(to_del->right);
			color = y->color;
			x = y->right;
			if (y->parent == to_del)
				x->parent = y;
			else
			{
				_transplant(y, y->right);
				y->right = to_del->right;
				y->right->parent = y;
			}
			_transplant(to_del, y);
			y->left = to_del->left;
			y->parent->left = y;
			y->color = color;
		}
		if (color == black)
			_del_fix(x);
	}

	node<T>	*search(const T &val) //needs to return iterators
	{
		node<T>	*searching = root;
		if (root == 0)
			return 0;
		while (1)
		{
			if (!searching)
				return 0;
			if (searching->value == val)
				return searching;
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
		// getwchar();
		real_print(ptr->left, space);
	}
	#endif

//private
	node<T>			*root;
	unsigned int	size;

	void	_del_fix(node<T> *x)
	{
		node<T> *s;
		while (x != root && x->color == black)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == red)
				{
					s->color = black;
					x->parent->color = red;
					left_rotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == black && s->right->color == black)
				{
					s->color = red;
					x = x->parent;
				}
				else
				{
					if (s->right->color == black)
					{
						s->left->color = black;
						s->color = red;
						right_rotate(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = black;
					s->right->color = black;
					left_rotate(x->parent);
					x = root;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == red)
				{
					s->color = black;
					x->parent->color = red;
					right_rotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == black && s->right->color == black)
				{
					s->color = red;
					x = x->parent;
				}
				else
				{
					if (s->left->color == black)
					{
						s->right->color = black;
						s->color = red;
						left_rotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = black;
					s->left->color = black;
					right_rotate(x->parent);
					x = root;
				}
			}
		}
		x->color = black;
	}

	node<T>	*_min(node<T> *tree)
	{
		if (!tree)
			return 0;
		while (tree->left)
			tree = tree->left;
		return tree;
	}

	node<T>	*_max(node<T> *tree)
	{
		if (!tree)
			return 0;
		while (tree->right)
			tree = tree->right;
		return tree;
	}

	void	_insert(node<T> *parent, node<T> *child)
	{
		node<T> *u;
		_add_simple_node(parent, child);
		if (!child->parent)
		{
			std::cerr << "No parent of child " << child->value << std::endl;
			return;
		}
		// std::cout << child->parent->parent << std::endl;
		while (child->parent->color == red)
		{
			std::cout << "GP: " << child->parent->parent << std::endl;
			if (child->parent == child->parent->parent->right)
			{
				u = child->parent->parent->left;
				if (u && u->color == red)
				{
					u->color = black;
					child->parent->color = black;
					child->parent->parent->color = red;
					child = child->parent->parent;
				}
				else
				{
					if (child == child->parent->left)
					{
						child = child->parent;
						right_rotate(child);
					}
					child->parent->color = black;
					child->parent->parent->color = red;
					left_rotate(child->parent->parent);
				}
			}
			else
			{
				u = child->parent->parent->right;

				if (u && u->color == red)
				{
					u->color = black;
					child->parent->color = black;
					child->parent->parent->color = red;
					child = child->parent->parent;
				}
				else
				{
					if (child == child->parent->right)
					{
						child = child->parent;
						left_rotate(child);
					}
					child->parent->color = black;
					child->parent->parent->color = red;
					right_rotate(child->parent->parent);
				}
			}
			if (child == root)
				break;
			if (child->parent->color == red)
				child->color = black;
		}
		root->color = black;
	}

	void	_add_simple_node(node<T> *p, node<T> *n)
	{
		if (!p)
		{
			root = n;
			n->color = black;
		}
		else if (!n)
			return;
		else if (p->value > n->value)
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

	void	_transplant(node<T> *orignal, node<T> *replacing)
	{
		if (orignal->parent == 0)
			root = replacing;
		else if (orignal->parent->left == orignal)
			orignal->parent->left = replacing;
		else
			orignal->parent->right = replacing;
		if (replacing)
			replacing->parent = orignal->parent;
	}

	// Solution -> recolor childs parent, GP and uncle
	// void	red_uncle(node<T> *parent)
	// {
	// 	parent->color *= -1;
	// 	parent->parent->color *= -1;
	// 	parent->borther()->color *= -1;
	// }

	// // Rotate parent in the opposite direction of child
	// void	black_triangle(node<T> *parent, node<T> *child)
	// {
	// 	if (parent->left == child)
	// 		right_rotate(parent);
	// 	else
	// 		left_rotate(parent);
	// }

	// //	Rotate GP in opposite direction of child 
	// //	and recolor original parent and GP of child.
	// void	black_line(node<T> *parent, node<T> *child)
	// {
	// 	node<T>	*GP = parent->parent;

	// 	std::cout << "Black line Child = " << child->value << " parent = " << parent->value << std::endl;
	// 	if (parent->left == child)
	// 		right_rotate(GP);
	// 	else
	// 		left_rotate(GP);
	// 	parent->color *= -1;
	// 	GP->color *= -1;
	// }

	void	left_rotate(node<T> *x)
	{
		node<T>	*y;
	
		y = x->right;
		if (!y)
			return ;
		x->right = y->left;
		if (y->left)
			y->left->parent = x;
		if (!x->parent)
			root = y;
		else
			_add_simple_node(x->parent, y);
		_add_simple_node(y, x);
	}

	void	right_rotate(node<T> *y)
	{
		node<T>	*x;
	
		x = y->right;
		if (!x)
			return ;
		y->left = x->right;
		if (x->right)
			x->right->parent = y;
		if (!y->parent)
			root = x;
		else
			_add_simple_node(y->parent, x);
		_add_simple_node(x, y);
	}

	void	left_right_rotate(node<T> *z)
	{
		node<T>	*x;

		x = z->left;
		if (!x)
			return ;
		left_rotate(x);
		right_rotate(z);
	}

	void	right_left_rotate(node<T> *z)
	{
		node<T>	*y;

		y = z->right;
		if (!y)
			return ;
		right_rotate(y);
		left_rotate(z);
	}
};

#endif