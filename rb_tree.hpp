/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:20 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/03 14:11:09 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <memory>

namespace ft
{
enum	colors
{
	black = 1,
	red = -1,
};

template <typename T>
struct	node
{
	T		value;
	node	*left;
	node	*right;
	node	*parent;
	int		color;
};


template <typename T, class Alloc = std::allocator<node<T> > >
class	tree
{
private:
	typedef struct node<T> node;

public:
	tree() {
		nd_null = alloc.allocate(1); // change to allocator
		nd_null->color = black;
		nd_null->left = 0;
		nd_null->right = 0;
		root = nd_null;
		size = 0;
	}
	tree (const tree &copy){
		root = copy.root; // NOT DEEP COPY, CHANGE WHEN ITERATION WORKS
		size = copy.size;
	}
	~tree() {
		_delete_everything(root);
		alloc.deallocate(nd_null, 1);
	};

	void	add(const T &val)
	{
		node	*p = root;
		node	*nv = alloc.allocate(1);
		nv->parent = 0;
		nv->value = val;
		nv->left = nd_null;
		nv->right = nd_null;
		nv->color = red;

		if (search(val) != 0)
		{
			alloc.deallocate(nv, 1);
			return;
		}
		size++;
		if (root != nd_null)
		{
			while (1)
			{
				if (val > p->value && p->right == nd_null)
					break;
				if (val < p->value && p->left == nd_null)
					break;
				if (val > p->value)
					p = p->right;
				else
					p = p->left;
			}
		}
		else
		{
			root = nv;
			nv->color = black;
			return;
		}
		nv->parent = p;
		if (nv->value > p->value)
			p->right = nv;
		else
			p->left = nv;

		if (nv->parent->parent == 0)
			return;
		_add_fix(nv);
	}

	void	del(const T &val)
	{
		node	*to_del = search(val);
		node	*to_fix, *y;
		int		og_color;

		if (!to_del)
			return;

		og_color = to_del->color;
		y = to_del;
		if (!to_del->left || to_del->left == nd_null)	// si on delete une node avec qu'un seul subtree
		{												// alors on a que a delete la node et mettre l'unique
			to_fix = to_del->right;							// subtree a la place
			_replace(to_del, to_del->right);
		}
		else if (!to_del->right || to_del->right == nd_null)
		{
			to_fix = to_del->left;
			_replace(to_del, to_del->left);
		}
		else
		{
			y = _min(to_del->right);
			og_color = y->color;
			to_fix = y->right;
			if (y->parent == to_del)
				to_fix->parent = y;
			else
			{
				_replace(y, y->right);
				y->right = to_del->right;
				y->right->parent = y;
			}
			_replace(to_del, y);
			y->left = to_del->left;
			y->left->parent = y;
			y->color = to_del->color;			
		}
		alloc.deallocate(to_del, 1);	// change to allocator shit when it works
		size--;
		if (og_color == black)
			_del_fix(to_fix);
			// std::cout << "fix" << std::endl;
	}

	node	*search(const T &val) //needs to return iterators note: maybe not depending on the implementation of iterators in map and set
	{
		node	*searching = root;
		if (root == 0)
			return 0;
		while (1)
		{
			if (searching == nd_null)
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

	void	real_print(node *ptr, int space)
	{
		if (!ptr || ptr == nd_null)
			return;
		space += 4;
		real_print(ptr->right, space);
		std::cout
			<< (ptr->color == black ? "\033[90m" : "\033[31m") << std::setw(space)
			<< ptr->value << "\033[0m" << std::endl;
		// getwchar();
		real_print(ptr->left, space);
	}
	#endif

//private
	node			*root;
	node			*nd_null;
	unsigned int	size;
	Alloc			alloc;

	node	*_min(node *tree)
	{
		if (!tree)
			return 0;
		while (tree->left && tree->left != nd_null)
			tree = tree->left;
		return tree;
	}

	node	*_max(node *tree)
	{
		if (!tree)
			return 0;
		while (tree->right && tree->right != nd_null)
			tree = tree->right;
		return tree;
	}

	void	_left_rotate(node *x)
	{
		node *y = x->right;
		x->right = y->left;
		if (y->left != nd_null)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == 0)
		{
			this->root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void _right_rotate(node *x)
	{
		node *y = x->left;
		x->left = y->right;
		if (y->right != nd_null)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == 0)
		{
			this->root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void	_add_fix(node *child)
	{
		node	*uncle;

		while(child->parent->color == red)
		{
			if (child->parent == child->parent->parent->right)
			{
				uncle = child->parent->parent->left;
				if (uncle->color == red)
				{
					uncle->color = black;
					child->parent->color = black;
					child->parent->parent->color = red;
					child = child->parent->parent;
				}
				else
				{
					if (child == child->parent->left)
					{
						child = child->parent;
						_right_rotate(child);
					}
					child->parent->color = black;
					child->parent->parent->color = red;
					_left_rotate(child->parent->parent);
				}
			}
			else
			{
				uncle = child->parent->parent->right;
				if (uncle->color == red)
				{
					uncle->color = black;
					child->parent->color = black;
					child->parent->parent->color = red;
					child = child->parent->parent;
				}
				else
				{
					if (child == child->parent->right)
					{
						child = child->parent;
						_left_rotate(child);
					}
					child->parent->color = black;
					child->parent->parent->color = red;
					_right_rotate(child->parent->parent);
				}
			}
			if (child == root)
				break;
		}
		root->color = black;
	}

	void	_replace(node *replaced, node *replacing)
	{
		if (!replaced->parent)
			root = replacing;
		else if (replaced == replaced->parent->left)
			replaced->parent->left = replacing;
		else
			replaced->parent->right = replacing;
		replacing->parent = replaced->parent;
	}

	void	_delete_everything(node *ptr)
	{
		if (!ptr || ptr == nd_null)
			return;
		_delete_everything(ptr->left);
		_delete_everything(ptr->right);
		delete ptr; 
	}

	void	_del_fix(node *ptr)
	{
		node *s;
		while (ptr != root && ptr->color == black)
		{
			if (ptr == ptr->parent->left)
			{
				s = ptr->parent->right;
				if (s->color == red)
				{
					s->color = black;
					ptr->parent->color = red;
					_left_rotate(ptr->parent);
					s = ptr->parent->right;
				}

				if (s->left->color == black && s->right->color == black)
				{
					s->color = red;
					ptr = ptr->parent;
				}
				else
				{
					if (s->right->color == black)
					{
						s->left->color = black;
						s->color = red;
						_right_rotate(s);
						s = ptr->parent->right;
					}

					s->color = ptr->parent->color;
					ptr->parent->color = black;
					s->right->color = black;
					_left_rotate(ptr->parent);
					ptr = root;
				}
			}
			else
			{
				s = ptr->parent->left;
				if (s->color == red)
				{
					s->color = black;
					ptr->parent->color = red;
					_right_rotate(ptr->parent);
					s = ptr->parent->left;
				}

				if (s->right->color == black && s->right->color == black)
				{
					s->color = red;
					ptr = ptr->parent;
				}
				else
				{
					if (s->left->color == black)
					{
						s->right->color = black;
						s->color = red;
						_left_rotate(s);
						s = ptr->parent->left;
					}

					s->color = ptr->parent->color;
					ptr->parent->color = black;
					s->left->color = black;
					_right_rotate(ptr->parent);
					ptr = root;
				}
			}
		}
		ptr->color = black;
	}
}; // fin de la class tree

} // fin du namespace ft

#endif