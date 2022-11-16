/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:38:23 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/16 16:56:58 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP

#include <functional>
#include <memory>
#include "rb_tree_map.hpp"

namespace ft
{

template <typename T,typename Category,
    class Compare = std::less<T>,
    class Allocator = std::allocator<T> >
class map_iterator
{
public: 
    typedef Category		iterator_category;
    typedef T				value_type;
    typedef std::ptrdiff_t	difference_type;
	typedef	value_type *	pointer;
	typedef	value_type &	reference;

	map_iterator(): _tr(), _curr(0) {}
	map_iterator(const map_iterator &c): _tr(c._tr), _curr(c._curr)	{}
	
	/**
	 * @brief Construct a new map_iterator for begin() or end()
	 * 
	 * @param tree		The tree of the iterator
	 * @param status	status at construction: False -> begin, True -> end
	**/
	map_iterator(const tree_map<T, Compare, Allocator> tree,
		bool status = false): _tr(tree), _curr((status ? _IT_MAP_MAGIC : 0)) {}

	reference	operator*()	const
	{
		if (_curr && _curr != _IT_MAP_MAGIC)
			return _curr->value;
		return _tr.get_nd_null()->value;
	}

	pointer		*operator->()	const
	{
		return &(operator*());
	}

	map_iterator	&operator++()	// faire en sorte que prev(0) return max et
	{								// que next(_MAGIC) return min()
		if (_tr.size == 0)
			return *this;
		_curr = _tr.next(_curr);
		return *this;
	}

	map_iterator	operator++(int)
	{
		map_iterator<T, Category, Compare, Allocator>	tmp(*this);

		++*this;
		return tmp;
	}

	map_iterator	&operator--()
	{
		if (_tr.size() == 0)
			return *this;
		_curr = _tr.prev(_curr);
	}

	map_iterator	operator--(int)
	{
		map_iterator<T, Category, Compare, Allocator>	tmp(*this);

		--*this;
		return tmp;
	}

	bool	operator == (const map_iterator &x)
	{
		map_iterator	tmp(*this);
		if (_comp(*tmp, x) && _comp(x, *tmp))
			return true;
		return false;
	}

	bool	operator != (const map_iterator &x)
	{
		return (!(*this == x));
	}
	
	bool	operator <  (const map_iterator &x)
	{
		map_iterator	tmp(*this);
		return (_comp(*tmp, x));
	}

private:
	const tree_map<T, Compare, Allocator>	_tr;
	node<T>				*_curr;
	const Allocator		_alloc;
	const Compare		_comp;
};

template <typename T,typename Category,
    class Compare = std::less<T>,
    class Allocator = std::allocator<T> >
class const_map_iterator
{
public: 
    typedef Category		iterator_category;
    typedef const T			value_type;
    typedef std::ptrdiff_t	difference_type;
	typedef	value_type *	pointer;
	typedef	value_type &	reference;

	const_map_iterator(): _tr(), _curr(0) {}
	const_map_iterator(const const_map_iterator &c): _tr(c._tr), _curr(c._curr)	{}
	
	/**
	 * @brief Construct a new const_map_iterator for begin() or end()
	 * 
	 * @param tree		The tree of the iterator
	 * @param status	status at construction: False -> begin, True -> end
	**/
	const_map_iterator(const tree_map<T, Compare, Allocator> tree,
		bool status = false): _tr(tree), _curr((status ? _IT_MAP_MAGIC : 0)) {}

	reference	operator*()	const
	{
		if (_curr && _curr != _IT_MAP_MAGIC)
			return _curr->value;
		return _tr.get_nd_null()->value;
	}

	pointer		*operator->()	const
	{
		return &(operator*());
	}

	const_map_iterator	&operator++()
	{								
		if (_tr.size == 0)
			return *this;
		_curr = _tr.next(_curr);
		return *this;
	}

	const_map_iterator	operator++(int)
	{
		const_map_iterator	tmp(*this);

		++*this;
		return tmp;
	}

	const_map_iterator	&operator--()
	{
		if (_tr.size() == 0)
			return *this;
		_curr = _tr.prev(_curr);
	}

	const_map_iterator	operator--(int)
	{
		const_map_iterator<T, Category, Compare, Allocator>	tmp(*this);

		--*this;
		return tmp;
	}

	bool	operator == (const const_map_iterator &x)
	{
		const_map_iterator<T, Category, Compare, Allocator>	tmp(*this);
		if (_comp(*tmp, x) && _comp(x, *tmp))
			return true;
		return false;
	}

	bool	operator != (const const_map_iterator &x)
	{
		return (!(*this == x));
	}
	
	bool	operator <  (const const_map_iterator &x)
	{
		const_map_iterator	tmp(*this);
		return (_comp(*tmp, x));
	}

private:
	const tree_map<T, Compare, Allocator>	_tr;
	node<T>				*_curr;
	const Allocator		_alloc;
	const Compare		_comp;
};

}

#endif