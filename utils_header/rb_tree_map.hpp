/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_map.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:20 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/23 14:02:09 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_MAP_HPP
#define RB_TREE_MAP_HPP

#include <memory>
#include <functional>
#include "iterator.hpp"
#include "pair.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
#ifndef	RB_TREE_SET_HPP
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
#endif

typedef enum e_throw_tree{
	begin = false,
	end = true
}	e_throw;

template <typename T, class Comp = std::less<T>, class Alloc = std::allocator<ft::node<T> > >
class	tree_map
{
private:
	typedef struct node<T> node;

public:
	class	rb_it;
	class	rb_cit;
	class	rb_rit;
	class	rb_crit;

	typedef	rb_it	iterator;
	typedef	rb_cit	const_iterator;

	tree_map()
	{
		std::allocator<T>	alloc_type;
		T					base;
	
		_nd_null = _alloc.allocate(1);
		alloc_type.construct(&_nd_null->value, base);
		_nd_null->color = black;
		_nd_null->left = 0;
		_nd_null->right = 0;
		_root = _nd_null;
		_size = 0;
	}
	explicit tree_map(const Comp &comp, const Alloc &alloc = Alloc())
	{
		std::allocator<T>	alloc_type;
		T					base;

		_comp = comp;
		_alloc = alloc;
		_nd_null = _alloc.allocate(1);
		alloc_type.construct(&_nd_null->value, base);
		_nd_null->color = black;
		_nd_null->left = 0;
		_nd_null->right = 0;
		_root = _nd_null;
		_size = 0;
	}
	tree_map (const tree_map &copy)
	{
		std::allocator<T>	alloc_type;
		T					base;

		_nd_null = _alloc.allocate(1);
		_nd_null->color = black;
		_nd_null->left = 0;
		_nd_null->right = 0;
		_root = _nd_null;
		_size = 0;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);
	}
	~tree_map()
	{
		std::allocator<T>	alloc_type;

		_delete_everything(_root);
		alloc_type.destroy(&_nd_null->value);
		_alloc.deallocate(_nd_null, 1);
	};

	tree_map &operator = (const tree_map &copy)
	{
		_delete_everything(this->_root);
		this->_root = this->_nd_null;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);

		return *this;
	}

	const tree_map &operator = (const tree_map &copy) const
	{
		_delete_everything(this->_root);
		this->_root = this->_nd_null;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);

		return *this;
	}

	node	*get_nd_null() const {return _nd_null;}

	Alloc	get_allocator()	const	{return _alloc;}

	bool	add(const T &val)
	{
		node	*p = _root;
		node	*nv;
		std::allocator<T>	alloc_type;

		if (search(val) != 0)
			return false;
		nv = _alloc.allocate(1);
		alloc_type.construct(&nv->value, val);
		nv->parent = 0;
		nv->left = _nd_null;
		nv->right = _nd_null;
		nv->color = red;

		_size++;
		if (_root != _nd_null)
		{
			while (1)
			{
				if (_comp(p->value, val) && p->right == _nd_null)
					break;
				if (_comp(val, p->value) && p->left == _nd_null)
					break;
				if (_comp(p->value, val))
					p = p->right;
				else
					p = p->left;
			}
		}
		else
		{
			_root = nv;
			nv->color = black;
			return true;
		}
		nv->parent = p;
		if (_comp(p->value, nv->value))
			p->right = nv;
		else
			p->left = nv;

		if (nv->parent->parent == 0)
			return true;
		_add_fix(nv);
		return true;
	}

	bool	del(const T &val)
	{
		node	*to_del = search(val);
		node	*to_fix, *y;
		int		og_color;
		std::allocator<T>	alloc_type;

		if (!to_del)
			return false;

		og_color = to_del->color;
		y = to_del;
		if (!to_del->left || to_del->left == _nd_null)
		{												
			to_fix = to_del->right;						
			_replace(to_del, to_del->right);
		}
		else if (!to_del->right || to_del->right == _nd_null)
		{
			to_fix = to_del->left;
			_replace(to_del, to_del->left);
		}
		else
		{
			y = min(to_del->right);
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
		alloc_type.destroy(&to_del->value);
		_alloc.deallocate(to_del, 1);
		_size--;
		if (og_color == black)
			_del_fix(to_fix);
		return true;
	}

	/**
	 * @brief		gives the next node based on ptr
	 * @exception	throws (e_throw_tree)end if we try to go PAST end
	 * 
	 * @param 		ptr 
	 * @return 		node<T> * -> next node of ptr 
	 */
	node	*next(node *ptr)	const
	{
		if (!ptr || ptr == _nd_null)
			throw (end);
		if (ptr == max(_root))
			return 0;
		if (ptr->right && ptr->right != _nd_null)
			return min(ptr->right);
		while (ptr->parent)
		{
			if (ptr == ptr->parent->left)
				return ptr->parent;
			else
				ptr = ptr->parent;
		}
		return ptr;
	}

	/**
	 * @brief		gives the previous node based on ptr
	 * @exception	throws (e_throw_tree)begin if we try to go before begin
	 * 
	 * @param ptr 
	 * @return node<T> * -> previous node of @a ptr 
	 */
	node	*prev(node *ptr)	const
	{
		if (!ptr || ptr == _nd_null)
			return max(_root);
		if (ptr == min(_root))
			throw (begin);
		if (ptr->left && ptr->left != _nd_null)
			return max(ptr->left);
		while (ptr->parent)
		{
			if (ptr == ptr->parent->right)
				return ptr->parent;
			else
				ptr = ptr->parent;
		}
		return ptr;
	}

	node	*search(const T &val)	const
	{
		node	*searching = _root;
		if (_root == 0)
			return 0;
		while (1)
		{
			if (searching == _nd_null)
				return 0;
			if (_comp_eq(searching->value, val))
				return searching;
			if (_comp(val, searching->value))
				searching = searching->left;
			else
				searching = searching->right;
		}
	}

	void	swap(ft::tree_map<T, Comp> &other)
	{
		node	*save_root, *save_null;
		unsigned int	save_size;
	
		save_null = _nd_null;
		save_root = _root;
		save_size = _size;
	
		_nd_null = other._nd_null;
		_root = other._root;
		_size = other._size;
		
		other._nd_null = save_null;
		other._root = save_root;
		other._size = save_size;
	}

	unsigned int	size() const {return _size;}

	node	*min()	const
	{
		node	*tree_map = _root;

		if (!tree_map)
			return 0;
		while (tree_map->left && tree_map->left != _nd_null)
			tree_map = tree_map->left;
		return tree_map;
	}

	node	*min(node *tree_map)	const
	{
		if (!tree_map)
			return 0;
		while (tree_map->left && tree_map->left != _nd_null)
			tree_map = tree_map->left;
		return tree_map;
	}

	node	*max()	const
	{
		node	*tree_map = _root;

		if (!tree_map)
			return 0;
		while (tree_map->right && tree_map->right != _nd_null)
			tree_map = tree_map->right;
		return tree_map;
	}

	node	*max(node *tree_map)	const
	{
		if (!tree_map)
			return 0;
		while (tree_map->right && tree_map->right != _nd_null)
			tree_map = tree_map->right;
		return tree_map;
	}

	void	clear()
	{
		_delete_everything(_root);
		_root = _nd_null;
	}

private:
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

	void	_right_rotate(node *x)
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
		std::allocator<T>	alloc_type;
		
		if (!ptr || ptr == _nd_null)
			return;
		_delete_everything(ptr->left);
		_delete_everything(ptr->right);
		alloc_type.destroy(&ptr->value);
		_alloc.deallocate(ptr, 1);
		_size--;
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

	inline bool	_comp_eq(const T &a, const T &b)	const
	{
		return !(_comp(a, b) || _comp(b, a));
	}

	node			*_root;
	node			*_nd_null;
	unsigned int	_size;
	Comp			_comp;
	Alloc			_alloc;
}; /* fin de la class tree_map */

} /* fin du namespace ft */

#endif