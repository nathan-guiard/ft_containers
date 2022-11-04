/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:20 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/04 14:26:56 by nguiard          ###   ########.fr       */
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


template <typename T, class Comp = std::less<T>, class Alloc = std::allocator<node<T> > >
class	tree
{
private:
	typedef struct node<T> node;

public:
	tree()
	{
		_nd_null = _alloc.allocate(1); 
		_nd_null->color = black;
		_nd_null->left = 0;
		_nd_null->right = 0;
		_root = _nd_null;
		_size = 0;
	}
	explicit tree(const Comp &comp, const Alloc &alloc = Alloc())
	{
		_comp = comp;
		_alloc = alloc;
		_nd_null = _alloc.allocate(1); 
		_nd_null->color = black;
		_nd_null->left = 0;
		_nd_null->right = 0;
		_root = _nd_null;
		_size = 0;
	}
	tree (const tree &copy)
	{
		_nd_null = _alloc.allocate(1); 
		_nd_null->color = black;
		_nd_null->left = 0;
		_nd_null->right = 0;
		_root = _nd_null;
		_size = 0;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);
	}
	~tree()
	{
		_delete_everything(_root);
		_alloc.deallocate(_nd_null, 1);
	};

	tree &operator = (const tree &copy)
	{
		_delete_everything(this->_root);
		this->_root = this->_nd_null;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);

		return *this;
	}

	void	add(const T &val)
	{
		node	*p = _root;
		node	*nv = _alloc.allocate(1);
		nv->parent = 0;
		nv->value = val;
		nv->left = _nd_null;
		nv->right = _nd_null;
		nv->color = red;

		if (search(val) != 0)
		{
			_alloc.deallocate(nv, 1);
			return;
		}
		_size++;
		if (_root != _nd_null)
		{
			while (1)
			{
				if (val > p->value && p->right == _nd_null)
					break;
				if (val < p->value && p->left == _nd_null)
					break;
				if (val > p->value)
					p = p->right;
				else
					p = p->left;
			}
		}
		else
		{
			_root = nv;
			nv->color = black;
			return;
		}
		nv->parent = p;
		if (p->value < nv->value)
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
		if (!to_del->left || to_del->left == _nd_null)	// si on delete une node avec qu'un seul subtree
		{												// alors on a que a delete la node et mettre l'unique
			to_fix = to_del->right;							// subtree a la place
			_replace(to_del, to_del->right);
		}
		else if (!to_del->right || to_del->right == _nd_null)
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
		_alloc.deallocate(to_del, 1);	// change to allocator shit when it works
		_size--;
		if (og_color == black)
			_del_fix(to_fix);
			// std::cout << "fix" << std::endl;
	}

	node	*search(const T &val) //needs to return iterators note: maybe not depending on the implementation of iterators in map and set
	{
		node	*searching = _root;
		if (_root == 0)
			return 0;
		while (1)
		{
			if (searching == _nd_null)
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
	void	print()	const
	{
		real_print(_root, 0);
	}

	void	real_print(node *ptr, int space)	const
	{
		if (!ptr || ptr == _nd_null)
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

//private:
	node	*_min(node *tree)
	{
		if (!tree)
			return 0;
		while (tree->left && tree->left != _nd_null)
			tree = tree->left;
		return tree;
	}

	node	*_max(node *tree)
	{
		if (!tree)
			return 0;
		while (tree->right && tree->right != _nd_null)
			tree = tree->right;
		return tree;
	}

	void	_left_rotate(node *x)
	{
		node *y = x->right;
		x->right = y->left;
		if (y->left != _nd_null)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == 0)
		{
			this->_root = y;
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
		if (y->right != _nd_null)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == 0)
		{
			this->_root = y;
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
			if (child == _root)
				break;
		}
		_root->color = black;
	}

	void	_replace(node *replaced, node *replacing)
	{
		if (!replaced->parent)
			_root = replacing;
		else if (replaced == replaced->parent->left)
			replaced->parent->left = replacing;
		else
			replaced->parent->right = replacing;
		replacing->parent = replaced->parent;
	}

	void	_delete_everything(node *ptr)
	{
		if (!ptr || ptr == _nd_null)
			return;
		_delete_everything(ptr->left);
		_delete_everything(ptr->right);
		delete ptr; 
	}

	void	_del_fix(node *ptr)
	{
		node *s;
		while (ptr != _root && ptr->color == black)
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
					ptr = _root;
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
					ptr = _root;
				}
			}
		}
		ptr->color = black;
	}

	void	_copy_helper(node *ptr, node *ptr_null)
	{
		if (!ptr || ptr == _nd_null || ptr == ptr_null)
			return;
		add(ptr->value);
		_copy_helper(ptr->left, ptr_null);
		_copy_helper(ptr->right, ptr_null);
	}

	node			*_root;
	node			*_nd_null;
	unsigned int	_size;
	Comp			_comp;
	Alloc			_alloc;
}; // fin de la class tree

} // fin du namespace ft

#endif