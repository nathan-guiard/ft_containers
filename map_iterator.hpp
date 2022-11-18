/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:38:23 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/18 15:11:46 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP

#include <functional>
#include <memory>
#include "rb_tree_map.hpp"

namespace ft
{

template <typename T, typename Category,
    class Compare = std::less<T> >
class map_iterator_base
{
public: 
    typedef Category		iterator_category;
    typedef T				value_type;
    typedef std::ptrdiff_t	difference_type;
	typedef	value_type *	pointer;
	typedef	value_type &	reference;

	map_iterator_base(): _tr(), _curr(0) {}
	map_iterator_base(const map_iterator_base &c): _tr(c._tr), _curr(c._curr)	{}
	
	/**
	 * @brief Construct a new map_iterator_base for begin() or end()
	 * 
	 * @param tree		The tree of the iterator
	 * @param status	status at construction: False -> begin, True -> end
	 * 
	**/
	map_iterator_base(const tree_map<value_type, Compare> *tree,
		bool status = false): _tr(tree),
		_curr((status ? 0 : _tr->min())) {}

	reference	operator*()	const
	{
		if (_curr)
			return _curr->value;
		return _tr->get_nd_null()->value;
	}

	pointer		*operator->()	const
	{
		return &(operator*());
	}

	map_iterator_base	&operator++()
	{								
		if (!_tr)
			return *this;
		try {
			_curr = _tr->next(_curr);
		} catch (e_throw) {};
		return *this;
	}

	map_iterator_base	operator++(int)
	{
		map_iterator_base<T, Category, Compare>	tmp(*this);

		++*this;
		return tmp;
	}

	map_iterator_base	&operator--()
	{								
		if (!_tr)
			return *this;
		try {
			_curr = _tr->prev(_curr);
		} catch (e_throw) {};
		return *this;
	}

	map_iterator_base	operator--(int)
	{
		map_iterator_base<T, Category, Compare>	tmp(*this);

		--*this;
		return tmp;
	}

	bool operator == (const map_iterator_base &y)	const
	{
		if (_tr && y._tr && (_tr->size() == 0 && y._tr->size() == 0))
			return true;
		if (_tr == y._tr && _curr && y._curr &&
			_comp_eq(_curr->value, y._curr->value))
			return true;
		if (_curr == y._curr)
			return true;
		return false;
	}

	bool	operator != (const map_iterator_base &x)
	{
		return (!(*this == x));
	}
	
	bool	operator <  (const map_iterator_base &x)
	{
		return (_comp(this->_curr->value, x._curr->value));
	}

private:
	inline bool	_comp_eq(const T &a, const T &b)	const
	{
		return !(_comp(a, b) || _comp(b, a));
	}

	const tree_map<T, Compare>	*_tr;
	node<T>		*_curr;
	Compare		_comp;
};


template <typename T, typename Category,
    class Compare = std::less<T> >
class map_iterator
{
public: 
    typedef Category		iterator_category;
    typedef T				value_type;
    typedef std::ptrdiff_t	difference_type;
	typedef	value_type *	pointer;
	typedef	value_type &	reference;

	map_iterator(): _b() {}
	map_iterator(const map_iterator &c): _b(c._b) {}
	map_iterator(const map_iterator_base<T, Category, Compare> &c): _b(c) {}
	
	/**
	 * @brief Construct a new map_iterator for begin() or end()
	 * 
	 * @param tree		The tree of the iterator
	 * @param status	status at construction: False -> begin, True -> end
	 * 
	**/
	explicit map_iterator(const tree_map<T, Compare> *tree,
		bool status = false): _b(tree, status) {}

	reference	operator*()	const
	{
		return *_b;
	}

	map_iterator_base<T, Category, Compare>	base()	const	{return _b;}

	pointer		operator->()	const
	{
		return &(operator*());
	}

	map_iterator	&operator++()
	{								
		_b++;
		return *this;
	}

	map_iterator	operator++(int)
	{
		map_iterator<T, Category, Compare>	tmp(*this);

		++*this;
		return tmp;
	}

	map_iterator	&operator--()
	{								
		_b--;
		return *this;
	}

	map_iterator	operator--(int)
	{
		map_iterator<T, Category, Compare>	tmp(*this);

		--*this;
		return tmp;
	}

	bool	operator == (const map_iterator &x)	const
	{
		return ((*this)._b == x._b);
	}

	bool	operator != (const map_iterator &x)	const
	{
		return (!(*this == x));
	}
	
	bool	operator <  (const map_iterator &x)	const
	{
		return ((*this)._b < x._b);
	}

private:
	map_iterator_base<T, Category, Compare>	_b;
};

template <typename T, typename Category,
    class Compare = std::less<T> >
class const_map_iterator
{
public: 
    typedef Category		iterator_category;
    typedef const T			value_type;
    typedef std::ptrdiff_t	difference_type;
	typedef	value_type *	pointer;
	typedef	value_type &	reference;

	const_map_iterator(): _b() {}
	const_map_iterator(const const_map_iterator &c): _b(c._b) {}
	const_map_iterator(const map_iterator<T, Category, Compare> &c):
		_b(c.base()) {}
	
	/**
	 * @brief Construct a new const_map_iterator for begin() or end()
	 * 
	 * @param tree		The tree of the iterator
	 * @param status	status at construction: False -> begin, True -> end
	 * 
	**/
	explicit const_map_iterator(const tree_map<T, Compare> *tree,
		bool status = false): _b(tree, status) {}

	reference	operator*()	const
	{
		return *_b;
	}

	pointer		operator->()	const
	{
		return &(operator*());
	}

	const_map_iterator	&operator++()
	{								
		_b++;
		return *this;
	}

	const_map_iterator	operator++(int)
	{
		const_map_iterator<T, Category, Compare>	tmp(*this);

		++*this;
		return tmp;
	}

	const_map_iterator	&operator--()
	{								
		_b--;
		return *this;
	}

	const_map_iterator	operator--(int)
	{
		const_map_iterator<T, Category, Compare>	tmp(*this);

		--*this;
		return tmp;
	}

	bool	operator == (const const_map_iterator &x)
	{
		return (this->_b == x._b);
	}

	bool	operator != (const const_map_iterator &x)
	{
		return (!(*this == x));
	}
	
	bool	operator <  (const const_map_iterator &x)
	{
		return ((*this)._b < x._b);
	}

private:
	map_iterator_base<T, Category, Compare>	_b;
};

}

#endif