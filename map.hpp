/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:15:13 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/15 14:41:24 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_MAP_HPP
#define		FT_MAP_HPP

#include 	<functional> //a surement enlever
#include	<memory>
#include	<map>	//a enlever
#include	"rb_tree.hpp"
#include	"pair.hpp"
#include	"iterator.hpp"
#include	"lexicographical_compare.hpp"
#include	"equal.hpp"

namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{

public:
	typedef	Key						key_type;
	typedef	T						mapped_type;
	typedef	ft::pair<const Key, T>	value_type;
	typedef	std::size_t				size_type;
	typedef	std::ptrdiff_t			difference_type;
	typedef	Compare 				key_compare;
	typedef	Allocator				allocator_type;
	typedef	value_type &			reference;
	typedef	const value_type &		const_reference;

	typedef	typename Allocator::pointer							pointer;
	typedef	typename Allocator::const_pointer					const_pointer;

	typedef	typename ft::tree<Key, Compare>::iterator				iterator;
	typedef	typename ft::tree<Key, Compare>::const_iterator			const_iterator;
	typedef	typename ft::tree<Key, Compare>::reverse_iterator		reverse_iterator;
	typedef	typename ft::tree<Key, Compare>::const_reverse_iterator	const_reverse_iterator;

	class value_compare
	{
	
	// friend class map<Key, T, Compare, Allocator>;
	
	public:
		typedef	bool		return_type;
		typedef	value_type	first_argument_type;
		typedef	value_type	second_argument_type;

		value_compare(Compare c) : comp(c) {}
	
		return_type	operator()(const first_argument_type &a,
							const second_argument_type &b)	const
		{ return comp(a.first, b.first); }
	
	protected:
		Compare	comp;
	};

	/*	MEMBER FUNCTIONS			*/
	/*	Constructors/Destructor		*/
	map() : _t() {};

	explicit map(const Compare &comp,
		const Allocator &alloc = Allocator()) : _t(comp, alloc) {} ;

	template <class InputIt>
	map(InputIt first, InputIt last,
		const Compare &comp = Compare(),
		const Allocator &alloc = Allocator()) : _t(comp, alloc)
	{
		if (++first == last)
		{
			_t.add(*first);
			return;
		}
		--first;
		for (; first != last; first++)
			_t.add(*first);
	}

	map(const map &other): _t(other._t) {};

	~map() {};

	map& operator = (const map &other)
	{
		this->_t = other._t;
		this->_comp = other._comp;
		this->_alloc = other._alloc;
	
		return *this;
	}

	allocator_type	get_allocator()	const
	{
		return _alloc;
	}

	/*	Element acces	*/
	Key			&at(const Key &key);
	const Key	&at(const Key &key)	const;
	Key	&operator[](const Key& key);

	/*	Iterators	*/
	iterator	begin()	{return iterator(&_t).begin();}
	iterator	end()	{return iterator(&_t).end();}
	const_iterator	begin()	const	{return const_iterator(&_t).begin();};
	const_iterator	end()	const	{return const_iterator(&_t).end();};
	reverse_iterator	rbegin() 	{return reverse_iterator(&_t).begin();};
	reverse_iterator	rend()		{return reverse_iterator(&_t).end();};
	const_reverse_iterator	rbegin()	const	{return const_reverse_iterator(&_t).begin();};
	const_reverse_iterator	rend()		const	{return const_reverse_iterator(&_t).end();};

	/*	Capacity	*/
	bool		empty()		const	{return (_t.size() ? true : false);}
	size_type	size()		const	{return _t.size();}
	size_type	max_size()	const	{return _t.get_allocator().max_size();}

	/*	Modifiers	*/
	void	clear() {_t.clear();}

	ft::pair<iterator, bool>	insert(const value_type& value)
	{
		iterator	save(&_t);
		iterator	it = begin();
		iterator	ite = end();
		bool		second;
	
		second = _t.add(value);
		save = find(value);
		ft::pair<iterator, bool>	p(save, second);
		return p;
	}

	template <class InputIt>
	void	insert(InputIt first, InputIt last)
	{
		for (; first != last; first++)
			_t.add(*first);
	}

	iterator	insert(iterator pos, const value_type &value)
	{
		(void)pos;
		_t.add(value);
		return find(value);
	}

	iterator	erase(iterator pos)
	{
		node<Key>	*nd = _t.search(*pos);
		Key	val = *pos;
		
		pos++;
		if (nd)
			_t.del(val);
		return pos;
	}

	size_type	erase(const Key &key)
	{
		node<Key>	*nd = _t.search(key);
		if (!nd)
			return 0;
		_t.del(key);
		return 1;
	}

	iterator	erase(iterator first, iterator last)
	{
		iterator save(first);
	
		if (first == begin() && last == end())
		{
			clear();
			return begin();
		}
		for (; first != last;)
		{
			save = first;
			save++;
			_t.del(*first);
			first = save;
		}
		return iterator(&_t);
	}

	void	swap(map &other)
	{
		_t.swap(other._t);
	}

	/*	Look up		*/
	size_type		count(const Key &key)	const
	{
		if (_t.search(key))
			return 1;
		return 0;
	}

	iterator		find(const Key &key)
	{
		iterator	it;
		iterator	ite;

		for (it = begin(), ite = end(); it != ite; it++)
		{
			if (*it == key)
				return it;
		}
		return ite;
	}
	
	const_iterator	find(const Key &key)	const
	{
		const_iterator	it;
		const_iterator	ite;

		for (it = begin(), ite = end(); it != ite; it++)
		{
			if (*it == key)
				return it;
		}
		return ite;
	}

	ft::pair<iterator, iterator>				equal_range(const Key &key)
	{
		ft::pair<iterator, iterator>	p;
	
		p.first = lower_bound(key);
		p.second = upper_bound(key);
	
		return p;
	}

	ft::pair<const_iterator, const_iterator>	equal_range(const Key &key)	const
	{
		ft::pair<const_iterator, const_iterator>	p;
	
		p.first = lower_bound(key);
		p.second = upper_bound(key);
	
		return p;
	}
	
	iterator	lower_bound(const Key &key)
	{
		iterator	res = begin();

		if (key <= *res)
			return res;
		if (_t.size() != 0 && *(--end()) < key)
			return end();
		while (*res < key)
			res++;
		return res;
	}
	
	const_iterator	lower_bound(const Key &key)	const
	{
		const_iterator	res = begin();

		if (key <= *res)
			return res;
		if (_t.size() != 0 && *(--end()) < key)
			return end();
		while (*res < key)
			res++;
		return res;
	}
	
	iterator	upper_bound(const Key &key)
	{
		iterator	res = begin();

		if (key <= *res)
			return res;
		if (_t.size() != 0 && *(--end()) < key)
			return end();
		while (*res <= key)
			res++;
		return res;
	}
	
	const_iterator	upper_bound(const Key &key)	const
	{
		const_iterator	res = begin();

		if (key <= *res)
			return res;
		if (_t.size() != 0 && *(--end()) < key)
			return end();
		while (*res <= key)
			res++;
		return res;
	}

	/*	Observers	*/
	key_compare	key_comp()	const	{return _comp;};
	
	value_compare	value_comp()	const {return _comp;};

friend bool	operator ==	(const ft::map<Key, Compare, Allocator> &lhs,
					const ft::map<Key, Compare, Allocator> &rhs)
{
	return (lhs.size() == rhs.size() &&
		ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

friend bool	operator !=	(const ft::map<Key, Compare, Allocator> &lhs,
					const ft::map<Key, Compare, Allocator> &rhs)
{
	return (!(lhs == rhs));
}

friend bool	operator <	(const ft::map<Key, Compare, Allocator> &lhs,
					const ft::map<Key, Compare, Allocator> &rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end()));	
}

friend bool	operator <=	(const ft::map<Key, Compare, Allocator> &lhs,
					const ft::map<Key, Compare, Allocator> &rhs)
{
	return (!(rhs < lhs));	
}

friend bool	operator >	(const ft::map<Key, Compare, Allocator> &lhs,
					const ft::map<Key, Compare, Allocator> &rhs)
{
	return (rhs < lhs);
}

friend bool	operator >=	(const ft::map<Key, Compare, Allocator> &lhs,
					const ft::map<Key, Compare, Allocator> &rhs)
{
	return (!(lhs < rhs));
}

private:
	Compare		_comp;
	Allocator	_alloc;
	ft::tree<value_type, value_compare>		_t;
};

}

#endif