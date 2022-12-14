/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:15:13 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/23 14:19:38 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_MAP_HPP
#define		FT_MAP_HPP

#include	<memory>
#include	<stdexcept>
#include	"utils_header/lexicographical_compare.hpp"
#include	"utils_header/equal.hpp"
#include	"utils_header/rb_tree_map.hpp"
#include	"utils_header/map_iterator.hpp"
#include	"utils_header/reverse_iterator.hpp"

namespace ft
{

template <class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
	class value_compare;

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

	typedef	typename ft::map_iterator<value_type,
		std::bidirectional_iterator_tag, value_compare>	iterator;

	typedef	typename ft::const_map_iterator<value_type,
		std::bidirectional_iterator_tag, value_compare>	const_iterator;

	typedef	typename ft::reverse_iterator<iterator, size_type>			reverse_iterator;
	typedef	typename ft::reverse_iterator<const_iterator, size_type>	const_reverse_iterator;

	class value_compare
	{
	
	public:
		typedef	bool		return_type;
		typedef	value_type	first_argument_type;
		typedef	value_type	second_argument_type;

		value_compare(): comp() {}
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
	T			&at(const Key &key)
	{
		iterator	it(find(key));
	
		if (it == end())
			throw (std::out_of_range("map::at"));
		return (*it).second;
	}

	const T		&at(const Key &key)	const
	{
		const_iterator	it(find(key));
	
		if (it == end())
			throw (std::out_of_range("map::at"));
		return (*it).second;
	}

	mapped_type	&operator[](const Key& key)
	{
		insert(value_type(key, mapped_type()));
		
		return ((*find(key)).second);
	}

	/*	Iterators	*/
	iterator	begin()				{return iterator(&_t, false);}
	iterator	end()				{return iterator(&_t, true);}
	const_iterator	begin()	const	{return const_iterator(&_t, false);};
	const_iterator	end()	const	{return const_iterator(&_t, true);};

	reverse_iterator	rbegin()
	{
		return reverse_iterator(end());
	};
	
	reverse_iterator	rend()
	{
		return reverse_iterator(begin());
	};

	const_reverse_iterator	rbegin()	const
	{
		return const_reverse_iterator(end());
	};
	
	const_reverse_iterator	rend()		const
	{
		return const_reverse_iterator(begin());
	};

	/*	Capacity	*/
	bool		empty()		const	{return (_t.size() == 0 ? true : false);}
	size_type	size()		const	{return _t.size();}
	size_type	max_size()	const	{return _t.get_allocator().max_size();}

	/*	Modifiers	*/
	void	clear() {_t.clear();}

	ft::pair<iterator, bool>	insert(const value_type& value)
	{
		iterator	first(&_t);
		bool		second;
	
		second = _t.add(value);
		first = find(value.first);
		ft::pair<iterator, bool>	p(first, second);
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
		return find(value.first);
	}

	iterator	erase(iterator pos)
	{
		node<value_type>	*nd = _t.search(*pos);
		value_type	val = *pos;
		
		pos++;
		if (nd)
			_t.del(val);
		return pos;
	}

	size_type	erase(const Key &key)
	{
		value_type	a = ft::make_pair<const Key, mapped_type>(key, mapped_type());

		node<value_type>	*nd = _t.search(a);
		if (!nd)
			return 0;
		_t.del(a);
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
		if (find(key) != end())
			return 1;
		return 0;
	}

	iterator		find(const Key &key)
	{
		iterator	it = begin();
		iterator	ite = end();

		for (; it != ite; it++)
		{
			if ((*it).first == key)
				return it;
		}
		return ite;
	}

	const_iterator	find(const Key &key)	const
	{
		const_iterator	it = begin();
		const_iterator	ite = end();

		for (; it != ite; it++)
		{
			if ((*it).first == key)
				return it;
		}
		return ite;
	}

	ft::pair<iterator, iterator>	equal_range(const Key &key)
	{
		ft::pair<iterator, iterator>	p;
	
		p.first = lower_bound(key);
		p.second = upper_bound(key);
	
		return p;
	}

	ft::pair<const_iterator, const_iterator>	equal_range(const Key &k) const
	{
		ft::pair<const_iterator, const_iterator>	p;
	
		p.first = lower_bound(k);
		p.second = upper_bound(k);
	
		return p;
	}

	iterator	lower_bound(const Key &key)
	{
		iterator	res = begin();

		if (key <= (*res).first)
			return res;
		if (_t.size() != 0 && (*(--end())).first < key)
			return end();
		while (res != end() && _comp((*res).first, key))
			res++;
		return res;
	}

	const_iterator	lower_bound(const Key &key)	const
	{
		const_iterator	res = begin();

		if (key <= (*res).first)
			return res;
		if (_t.size() != 0 && (*(--end())).first < key)
			return end();
		while (res != end() && _comp((*res).first, key))
			res++;
		return res;
	}
	
	iterator	upper_bound(const Key &key)
	{
		iterator	res = lower_bound(key);
		
		if (res == find(key))
			res++;
		return res;
	}
	
	const_iterator	upper_bound(const Key &key)	const
	{
		const_iterator	res = lower_bound(key);
		
		if (res == find(key))
			res++;
		return res;
	}

	/*	Observers	*/
	key_compare	key_comp()	const	{return _comp;};
	
	value_compare	value_comp()	const
	{
		return value_compare();
	};

bool	operator ==	(const ft::map<Key, T, Compare, Allocator> &rhs)	const
{
	return (this->size() == rhs.size() &&
		ft::equal(this->begin(), this->end(), rhs.begin(), rhs.end()));
}

bool	operator !=	(const ft::map<Key, T, Compare, Allocator> &rhs)	const
{
	return (!(*this == rhs));
}

bool	operator <	(const ft::map<Key, T, Compare, Allocator> &rhs)	const
{
	return (ft::lexicographical_compare<const_iterator,
										const_iterator,
										_comp_iterators<const_iterator,
														Compare> >
		(this->begin(), this->end(), rhs.begin(), rhs.end())
		);	
}

bool	operator <=	(const ft::map<Key, T, Compare, Allocator> &rhs)	const
{
	return (!(rhs < *this));	
}

bool	operator >	(const ft::map<Key, T, Compare, Allocator> &rhs)	const
{
	return (rhs < *this);
}

bool	operator >=	(const ft::map<Key, T, Compare, Allocator> &rhs)	const
{
	return (!(*this < rhs));
}

private:
	Compare		_comp;
	Allocator	_alloc;
	ft::tree_map<value_type, value_compare>		_t;

	template<class it, class _comp>
	class _comp_iterators
	{
	public:
		_comp_iterators(): _cmp_it(_comp()) {}
		_comp_iterators(const _comp_iterators &c): _cmp_it(c._cmp_it) {}
		~_comp_iterators() {}
	
		_comp_iterators &operator = (const _comp_iterators &a) {_cmp_it = a._cmp_it;}
		bool	operator()(const it &a, const it &b)
		{
			return _cmp_it((*a).second, (*b).second);
		}
	private:
		_comp	_cmp_it;
	};
};

}/* fin namespace ft */

#endif