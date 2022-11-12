/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:20 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/12 16:11:03 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <memory>
#include "iterator.hpp"

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
	class	rb_it;
	class	rb_cit;
	class	rb_rit;
	class	rb_crit;

	typedef	rb_it	iterator;
	typedef	rb_cit	const_iterator;
	typedef	rb_rit	reverse_iterator;
	typedef	rb_crit	const_reverse_iterator;

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

	const tree &operator = (const tree &copy) const
	{
		_delete_everything(this->_root);
		this->_root = this->_nd_null;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);

		return *this;
	}

	class rb_it : iterator_traits<std::bidirectional_iterator_tag, T>
	{
	public:
		rb_it(): _tr(), _is_end(false), _has_been_alloc(true), _alloc()
		{
			T	val = T();

			_nd_null = _alloc.allocate(1);
			_nd_null->color = black;
			_nd_null->left = 0;
			_nd_null->right = 0;
			_nd_null->value = val;
			_curr = _nd_null;
		}

		rb_it(const iterator &copy): _tr(copy._tr), _curr(copy._curr), _nd_null(copy._nd_null),
			_is_end(copy._is_end), _has_been_alloc(copy._has_been_alloc), _alloc()  {}

		rb_it(const const_iterator &copy): _tr(copy.get_tree()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(copy.get_been_alloc()) {};
		
		rb_it(const const_iterator &copy, bool has_been_alloc): _tr(copy.get_tree()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(has_been_alloc) {};

		rb_it(tree *tr): _tr(tr), _curr(tr->min()),
			_nd_null(tr->get_nd_null()), _has_been_alloc(false), _alloc()
		{
			_is_end = false;
			if (_curr == 0)
				_is_end = true;
		}

		~rb_it() {if (_has_been_alloc) _alloc.deallocate(_nd_null, 1);}

		iterator &operator = (const iterator &copy)
		{
			if (_has_been_alloc)
				_alloc.deallocate(_nd_null, 1);
			_tr = copy._tr;
			_curr = copy._curr;
			_nd_null = copy._nd_null;
			_is_end = copy._is_end;
			_has_been_alloc = copy._has_been_alloc;
		

			return *this;
		}

		tree	*get_tree()	const		{return _tr;}

		node	*get_curr()	const		{return _curr;}

		node	*get_it_null()	const	{return _nd_null;}
	
		bool	get_is_end()	const	{return _is_end;}
	
		bool	get_been_alloc()	const	{return _has_been_alloc;}
	
		const T &operator*() const
		{
			if (_curr && _curr != _nd_null)
				return _curr->value;
			return _nd_null->value;
		}

		const T *operator->() const
		{
			if (_curr)
				return &_curr->value;
			return &_nd_null->value;
		}

		iterator	&operator++()
		{
			if (!_curr || _curr == _nd_null || _tr->size() == 0 || _is_end)
				return *this;
			_curr = _tr->next(_curr);
			if (!_curr)
				_is_end = true;
			return *this;
		}

		iterator	operator++(int)
		{
			iterator	tmp;

			tmp = *this;
			++*this;
			return tmp;
		}

		iterator	&operator--()
		{
			if (!_tr)
				return *this;
			if (_tr->size() == 0)
				return *this;
			if (_is_end || !_curr || _curr == _nd_null)
			{
				_is_end = false;
				_curr = _tr->max();
			}
			else
				_curr = _tr->prev(_curr);
			return *this;
			
		}

		iterator	operator--(int)
		{
			iterator	tmp;

			tmp = *this;
			--*this;
			return tmp;
		}

		iterator	begin()
		{
			_curr = _tr->min();
			if (!_curr)
				_is_end = true;
			
			return *this;
		}

		iterator	end()
		{
			_curr = 0;
			_is_end = true;
		
			return *this;
		}

	bool operator == (const iterator &y)	const
	{
		if (_curr == y._curr)
			return true;
		return false;
	}

	bool operator != (const iterator &y)	const	{return (!(*this == y));}

	bool operator <  (const iterator &y)	const
	{
		if (_curr < y._curr)
			return true;
		return false;
	}

	private:
		tree	*_tr;
		node	*_curr;
		node	*_nd_null;
		bool	_is_end;
		bool	_has_been_alloc;
		Alloc	_alloc;
	};

	class rb_cit : iterator_traits<std::bidirectional_iterator_tag, T>
	{
	public:
		rb_cit(): _tr(), _is_end(false), _has_been_alloc(true), _alloc()
		{
			T	val = T();

			_nd_null = _alloc.allocate(1);
			_nd_null->color = black;
			_nd_null->left = 0;
			_nd_null->right = 0;
			_nd_null->value = val;
			_curr = _nd_null;
		}

		rb_cit(const const_iterator &copy): _tr(copy._tr), _curr(copy._curr), _nd_null(copy._nd_null),
			_is_end(copy._is_end), _has_been_alloc(copy._has_been_alloc), _alloc()  {}

		rb_cit(const iterator &copy): _tr(copy.get_tree()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(copy.get_been_alloc()) {};
		
		rb_cit(const iterator &copy, bool has_been_alloc): _tr(copy.get_tree()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(has_been_alloc) {};

		rb_cit(const tree *tr): _tr(tr), _curr(tr->min()),
			_nd_null(tr->get_nd_null()), _has_been_alloc(false), _alloc()
		{
			_is_end = false;
			if (_curr == 0)
				_is_end = true;
		}

		~rb_cit()
		{
			if (_has_been_alloc == true)
				_alloc.deallocate(_nd_null, 1);
		}

		const_iterator &operator = (const const_iterator &copy)
		{
			if (_has_been_alloc)
				_alloc.deallocate(_nd_null, 1);
			_tr = copy._tr;
			_curr = copy._curr;
			_nd_null = copy._nd_null;
			_is_end = copy._is_end;
			_has_been_alloc = copy._has_been_alloc;
		
			return *this;
		}

		tree	*get_tree()	const		{return _tr;}

		node	*get_curr()	const		{return _curr;}

		node	*get_it_null()	const	{return _nd_null;}
	
		bool	get_is_end()	const	{return _is_end;}
	
		bool	get_been_alloc()	const	{return _has_been_alloc;}

		const T &operator*() const
		{
			if (_curr && _curr != _nd_null)
				return _curr->value;
			return _nd_null->value;
		}

		const T *operator->() const
		{
			if (_curr)
				return &_curr->value;
			return &_nd_null->value;
		}

		const_iterator	&operator++()
		{
			if (!_curr || _curr == _nd_null || _tr->size() == 0 || _is_end)
				return *this;
			_curr = _tr->next(_curr);
			if (!_curr)
				_is_end = true;
			return *this;
		}

		const_iterator	operator++(int)
		{
			const_iterator	tmp;

			tmp = *this;
			++*this;
			return tmp;
		}

		const_iterator	&operator--()
		{
			if (_tr->size() == 0)
				return *this;
			if (*this == this->end())
			{
				_is_end = false;
				_curr = _tr->max();
			}
			if (_is_end || !_curr || _curr == _nd_null)
			{
				_is_end = false;
				_curr = _tr->max();
			}
			else
				_curr = _tr->prev(_curr);
			return *this;
		}

		const_iterator	operator--(int)
		{
			const_iterator	tmp;

			tmp = *this;
			--*this;
			return tmp;
		}

		const_iterator	begin()
		{
			_curr = _tr->min();
			if (!_curr)
				_is_end = true;
			
			return *this;
		}

		const_iterator	end()
		{
			_curr = 0;
			_is_end = true;
		
			return *this;
		}

	bool operator == (const const_iterator &y)	const
	{
		if (_curr == y._curr)
			return true;
		return false;
	}

	bool operator != (const const_iterator &y)	const	{return (!(*this == y));}

	bool operator <  (const const_iterator &y)	const
	{
		if (_curr < y._curr)
			return true;
		return false;
	}

	private:
		const tree	*_tr;
		node	*_curr;
		node	*_nd_null;
		bool	_is_end;
		bool	_has_been_alloc;
		Alloc	_alloc;
	};

	class rb_rit : iterator_traits<std::bidirectional_iterator_tag, T>
	{
	public:
		rb_rit(): _b() {}

		rb_rit(const reverse_iterator &copy): _b(copy._b, false) {}

		rb_rit(const const_iterator &copy): _b(copy, false) {};

		rb_rit(tree *tr): _b(tr) {}

		~rb_rit() {}

		reverse_iterator &operator = (const reverse_iterator &copy)
		{
			_b = copy._b;
			return *this;
		}

		iterator	base()	const	{return _b;}

		const T &operator*() const
		{
			return *_b;
		}

		const T *operator->() const
		{
			return &_b.get_curr()->value;
		}

		reverse_iterator	&operator++()
		{
			_b--;
			return *this;
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp;

			tmp = *this;
			++*this;
			return tmp;
		}

		reverse_iterator	&operator--()
		{
			_b++;
			return *this;
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp;

			tmp = *this;
			--*this;
			return tmp;
		}

		reverse_iterator	begin()
		{
			_b = iterator(_b.get_tree()).end();
			_b--;

			return *this;
		}

		reverse_iterator	end()
		{
			_b = iterator(_b.get_tree()).begin();
			_b--;

			return *this;
		}
		

	bool operator == (const reverse_iterator &y)	const
	{
		if (_b.get_curr() == y._b.get_curr())
			return true;
		return false;
	}

	bool operator != (const reverse_iterator &y)	const	{return (!(*this == y));}

	bool operator <  (const reverse_iterator &y)	const
	{
		if (_b.get_curr() < y._b.get_curr())
			return true;
		return false;
	}

	private:
		iterator	_b;
	};

	class rb_crit : iterator_traits<std::bidirectional_iterator_tag, T>
	{
	public:
		rb_crit(): _b() {}

		rb_crit(const const_reverse_iterator &copy): _b(copy._b, false) {}

		rb_crit(const reverse_iterator &copy): _b(copy.base(), false) {}

		rb_crit(const const_iterator &copy): _b(copy, false) {};

		rb_crit(tree *tr): _b(tr) {}

		~rb_crit() {}

		const_reverse_iterator &operator = (const const_reverse_iterator &copy)
		{
			_b = copy._b;
			return *this;
		}

		iterator	base()	const	{return _b;}

		const T &operator*() const
		{
			return *_b;
		}

		const T *operator->() const
		{
			return &_b.get_curr()->value;
		}

		const_reverse_iterator	&operator++()
		{
			_b--;
			return *this;
		}

		const_reverse_iterator	operator++(int)
		{
			const_reverse_iterator	tmp;

			tmp = *this;
			++*this;
			return tmp;
		}

		const_reverse_iterator	&operator--()
		{
			_b++;
			return *this;
		}

		const_reverse_iterator	operator--(int)
		{
			const_reverse_iterator	tmp;

			tmp = *this;
			--*this;
			return tmp;
		}

		const_reverse_iterator	begin()
		{
			_b = iterator(_b.get_tree()).end();
			_b--;

			return *this;
		}

		const_reverse_iterator	end()
		{
			_b = iterator(_b.get_tree()).begin();
			_b--;

			return *this;
		}
		

	bool operator == (const const_reverse_iterator &y)	const
	{
		if (_b.get_curr() == y._b.get_curr())
			return true;
		return false;
	}

	bool operator != (const const_reverse_iterator &y)	const	{return (!(*this == y));}

	bool operator <  (const const_reverse_iterator &y)	const
	{
		if (_b.get_curr() < y._b.get_curr())
			return true;
		return false;
	}

	private:
		iterator	_b;
	};

	node	*get_nd_null() const {return _nd_null;}

	bool	add(const T &val)
	{
		node	*p = _root;
		node	*nv;
	
		if (search(val) != 0)
			return false;
		
		nv = _alloc.allocate(1);
		_alloc.construct(nv, *nv);
		nv->parent = 0;
		nv->value = val;
		nv->left = _nd_null;
		nv->right = _nd_null;
		nv->color = red;

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
			return true;
		}
		nv->parent = p;
		if (p->value < nv->value)
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

		if (!to_del)
			return false;

		og_color = to_del->color;
		y = to_del;
		if (!to_del->left || to_del->left == _nd_null)	// si on delete une node avec qu'un seul subtree
		{												// alors on a que a delete la node et mettre l'unique
			to_fix = to_del->right;						// subtree a la place
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
		_alloc.deallocate(to_del, 1);
		_size--;
		if (og_color == black)
			_del_fix(to_fix);
		return true;
	}

	node	*next(node *ptr)	const
	{
		if (!ptr || ptr == _nd_null)
			return 0;
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

	node	*prev(node *ptr)	const
	{
		if (!ptr || ptr == _nd_null)
			return 0;
		if (ptr == min(_root))
			return 0;
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
			if (searching->value == val)
				return searching;
			if (searching->value > val)
				searching = searching->left;
			else
				searching = searching->right;
		}
	}

	unsigned int	size() const {return _size;}

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

	node	*min()	const
	{
		node	*tree = _root;

		if (!tree)
			return 0;
		while (tree->left && tree->left != _nd_null)
			tree = tree->left;
		return tree;
	}

	node	*min(node *tree)	const
	{
		if (!tree)
			return 0;
		while (tree->left && tree->left != _nd_null)
			tree = tree->left;
		return tree;
	}

	node	*max()	const
	{
		node	*tree = _root;

		if (!tree)
			return 0;
		while (tree->right && tree->right != _nd_null)
			tree = tree->right;
		return tree;
	}

	node	*max(node *tree)	const
	{
		if (!tree)
			return 0;
		while (tree->right && tree->right != _nd_null)
			tree = tree->right;
		return tree;
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
		if (!ptr || ptr == _nd_null)
			return;
		_delete_everything(ptr->left);
		_delete_everything(ptr->right);
		_alloc.deallocate(ptr, 1);
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