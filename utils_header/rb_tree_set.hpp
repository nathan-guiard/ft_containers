/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_set.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:20 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/23 14:20:58 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_SET_HPP
#define RB_TREE_SET_HPP

#include <memory>
#include <functional>
#include "iterator.hpp"
#include "pair.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"


namespace ft
{
#ifndef RB_TREE_MAP_HPP
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


template <typename T, class Comp = std::less<T>, class Alloc = std::allocator<node<T> > >
class	tree_set
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

	tree_set()
	{
		_nd_null = _alloc.allocate(1); 
		_nd_null->color = black;
		_nd_null->left = 0;
		_nd_null->right = 0;
		_root = _nd_null;
		_size = 0;
	}
	explicit tree_set(const Comp &comp, const Alloc &alloc = Alloc()) : _comp(Comp())
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
	tree_set (const tree_set &copy)
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
	~tree_set()
	{
		_delete_everything(_root);
		_alloc.deallocate(_nd_null, 1);
	};

	tree_set &operator = (const tree_set &copy)
	{
		_delete_everything(this->_root);
		this->_root = this->_nd_null;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);

		return *this;
	}

	const tree_set &operator = (const tree_set &copy) const
	{
		_delete_everything(this->_root);
		this->_root = this->_nd_null;
		if (copy._root && copy._root != copy._nd_null)
			_copy_helper(copy._root, copy._nd_null);

		return *this;
	}

	/*	ITERATORS	*/
class rb_it : iterator_traits<std::bidirectional_iterator_tag, T>
	{
	public:
		rb_it(): _tr(), _is_end(false), _has_been_alloc(true), _alloc()
		{
			T	val = T();
			std::allocator<T>	alloc_type;

			_nd_null = _alloc.allocate(1);
			alloc_type.construct(&_nd_null->value, val);
			_nd_null->color = black;
			_nd_null->left = 0;
			_nd_null->right = 0;
			_curr = _nd_null;
		}

		rb_it(const iterator &copy): _tr(copy._tr), _curr(copy._curr), _nd_null(copy._nd_null),
			_is_end(copy._is_end), _has_been_alloc(copy._has_been_alloc), _alloc()  {}

		rb_it(const const_iterator &copy): _tr(copy.get_tree_set()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(copy.get_been_alloc()) {};

		rb_it(const const_iterator &copy, bool has_been_alloc): _tr(copy.get_tree_set()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(has_been_alloc) {};

		rb_it(tree_set *tr): _tr(tr), _curr(tr->min()),
			_nd_null(tr->get_nd_null()), _has_been_alloc(false), _alloc()
		{
			_is_end = false;
			if (_curr == 0)
				_is_end = true;
		}

		~rb_it()
		{
			std::allocator<T>	alloc_type;
			if (_has_been_alloc)
			{
				alloc_type.destroy(&_nd_null->value);
				_alloc.deallocate(_nd_null, 1);
			}
		}

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

		const tree_set	*get_tree_set()	const		{return _tr;}

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
			if (!_tr || !_curr)
				return *this;
			_curr = _tr->next(_curr);
			if (!_curr)
				_is_end = true;
			return *this;
		}

		iterator	operator++(int)
		{
			iterator	tmp(*this);

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
			if (_tr->size() == 0)
				return(end());
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
		if (_tr == y._tr && _curr && y._curr &&
			_comp_eq(_curr->value, y._curr->value))
			return true;
		if (_curr == y._curr)
			return true;
		return false;
	}

	bool operator != (const iterator &y)	const	{return (!(*this == y));}

	bool operator <  (const iterator &y)	const
	{
		if (_curr && y._curr && _comp(_curr->value, y._curr->value))
			return true;
		if (_curr < y._curr)
			return true;
		return false;
	}

	inline bool	_comp_eq(const T &a, const T &b)	const
	{
		return !(_comp(a, b) || _comp(b, a));
	}

	private:
		const tree_set	*_tr;
		node	*_curr;
		node	*_nd_null;
		bool	_is_end;
		bool	_has_been_alloc;
		Alloc	_alloc;
		Comp	_comp;
	};

class rb_cit : iterator_traits<std::bidirectional_iterator_tag, T>
	{
	public:
		rb_cit(): _tr(), _is_end(false), _has_been_alloc(true), _alloc()
		{
			T	val = T();
			std::allocator<T>	alloc_type;

			_nd_null = _alloc.allocate(1);
			alloc_type.construct(&_nd_null->value, val);
			_nd_null->color = black;
			_nd_null->left = 0;
			_nd_null->right = 0;
			_nd_null->value = val;
			_curr = _nd_null;
		}

		rb_cit(const const_iterator &copy): _tr(copy._tr), _curr(copy._curr), _nd_null(copy._nd_null),
			_is_end(copy._is_end), _has_been_alloc(copy._has_been_alloc), _alloc()  {}

		rb_cit(const iterator &copy): _tr(copy.get_tree_set()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(copy.get_been_alloc()) {};
		
		rb_cit(const iterator &copy, bool has_been_alloc): _tr(copy.get_tree_set()),
			_curr(copy.get_curr()), _nd_null(copy.get_it_null()),
			_is_end(copy.get_is_end()), _has_been_alloc(has_been_alloc) {};

		rb_cit(const tree_set *tr): _tr(tr), _curr(tr->min()),
			_nd_null(tr->get_nd_null()), _has_been_alloc(false), _alloc()
		{
			_is_end = false;
			if (_curr == 0)
				_is_end = true;
		}

		~rb_cit()
		{
			std::allocator<T>	alloc_type;
			if (_has_been_alloc)
			{
				alloc_type.destroy(&_nd_null->value);
				_alloc.deallocate(_nd_null, 1);
			}
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

		const tree_set	*get_tree_set()	const		{return _tr;}

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
			if (!_curr || !_tr)
				return *this;
			_curr = _tr->next(_curr);
			if (!_curr)
				_is_end = true;
			return *this;
		}

		const_iterator	operator++(int)
		{
			const_iterator	tmp(*this);
		
			++*this;
			return tmp;
		}

		const_iterator	&operator--()
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

		const_iterator	operator--(int)
		{
			const_iterator	tmp;

			tmp = *this;
			--*this;
			return tmp;
		}

		const_iterator	begin()
		{
			if (_tr->size() == 0)
				return(end());
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
		if (_tr == y._tr && _curr && y._curr && _curr->value == y._curr->value)
			return true;
		if (_curr == y._curr)
			return true;
		return false;
	}

	bool operator != (const const_iterator &y)	const	{return (!(*this == y));}

	bool operator <  (const const_iterator &y)	const
	{
		if (_curr && y._curr && _comp(_curr->value, y._curr->value))
			return true;
		if (_curr && y._curr && (_comp_eq(_curr->value, y._curr->value)
			|| _comp(y._curr->value, _curr->value)))
			return false;
		if (_curr < y._curr)
			return true;
		return false;
	}

	inline bool	_comp_eq(const T &a, const T &b)	const
	{
		return !(_comp(a, b) || _comp(b, a));
	}

	private:
		const tree_set	*_tr;
		node	*_curr;
		node	*_nd_null;
		bool	_is_end;
		bool	_has_been_alloc;
		Alloc	_alloc;
		Comp	_comp;
	};

	class rb_rit : iterator_traits<std::bidirectional_iterator_tag, T>
	{
	public:
		rb_rit(): _b() {}

		rb_rit(const reverse_iterator &copy): _b(copy._b, false) {}

		rb_rit(const const_iterator &copy): _b(copy, false) {};

		rb_rit(tree_set *tr): _b(tr) {}

		~rb_rit() {}

		reverse_iterator &operator = (const reverse_iterator &copy)
		{
			_b = copy._b;
			return *this;
		}

		iterator	base()	const	{return _b;}

		const T &operator*() const
		{
			iterator	tmp(_b);
			return *(--tmp);
		}

		const T *operator->() const
		{
			return &(this->operator*());
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
			_b = iterator(_b.get_tree_set()).end();

			return *this;
		}

		reverse_iterator	end()
		{
			_b = iterator(_b.get_tree_set()).begin();

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

		rb_crit(tree_set *tr): _b(tr) {}

		~rb_crit() {}

		const_reverse_iterator &operator = (const const_reverse_iterator &copy)
		{
			_b = copy._b;
			return *this;
		}

		iterator	base()	const	{return _b;}

		const T &operator*() const
		{
			iterator	tmp(_b);
			return *(--tmp);
		}

		const T *operator->() const
		{
			return &(this->operator*());
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
			_b = iterator(_b.get_tree_set()).end();

			return *this;
		}

		const_reverse_iterator	end()
		{
			_b = iterator(_b.get_tree_set()).begin();

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
			if (_comp_eq(searching->value, val))
				return searching;
			if (_comp(val, searching->value))
				searching = searching->left;
			else
				searching = searching->right;
		}
	}

	void	swap(ft::tree_set<T, Comp> &other)
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
		node	*tree_set = _root;

		if (!tree_set)
			return 0;
		while (tree_set->left && tree_set->left != _nd_null)
			tree_set = tree_set->left;
		return tree_set;
	}

	node	*min(node *tree_set)	const
	{
		if (!tree_set)
			return 0;
		while (tree_set->left && tree_set->left != _nd_null)
			tree_set = tree_set->left;
		return tree_set;
	}

	node	*max()	const
	{
		node	*tree_set = _root;

		if (!tree_set)
			return 0;
		while (tree_set->right && tree_set->right != _nd_null)
			tree_set = tree_set->right;
		return tree_set;
	}

	node	*max(node *tree_set)	const
	{
		if (!tree_set)
			return 0;
		while (tree_set->right && tree_set->right != _nd_null)
			tree_set = tree_set->right;
		return tree_set;
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
}; /* fin de la class tree_set */

} /* fin du namespace ft */

#endif