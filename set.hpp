/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:15:13 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/13 20:49:25 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_SET_HPP
#define		FT_SET_HPP

#include 	<functional> //a surement enlever
#include	<memory>
#include	<set>	//a enlever
#include	"rb_tree.hpp"
#include	"pair.hpp"
#include	"iterator.hpp"
#include	"lexicographical_compare.hpp"
#include	"equal.hpp"

namespace ft
{

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set
{

public:
	typedef	Key					key_type;
	typedef	Key					value_type;
	typedef	std::size_t			size_type;
	typedef	std::ptrdiff_t		difference_type;
	typedef	Compare 			key_compare;
	typedef	Compare 			value_compare;
	typedef	Allocator			allocator_type;
	typedef	value_type &		reference;
	typedef	const value_type &	const_reference;

	typedef	typename Allocator::pointer							pointer;
	typedef	typename Allocator::const_pointer					const_pointer;

	typedef	typename ft::tree<Key, Compare>::iterator				iterator;
	typedef	typename ft::tree<Key, Compare>::const_iterator			const_iterator;
	typedef	typename ft::tree<Key, Compare>::reverse_iterator		reverse_iterator;
	typedef	typename ft::tree<Key, Compare>::const_reverse_iterator	const_reverse_iterator;

	/*	MEMBER FUNCTIONS			*/
	/*	Constructors/Destructor		*/
	set() : _t() {};

	explicit set(const Compare &comp,
		const Allocator &alloc = Allocator()) : _t(comp, alloc) {} ;

	template <class InputIt>
	set(InputIt first, InputIt last,
		const Compare &comp = Compare(),
		const Allocator &alloc = Allocator()) : _t(comp, alloc)
	{
		if (first == last)
		{
			_t.add(*first);
			return;
		}
		for (; first != last; first++)
			_t.add(*first);
	}

	~set() {};

	set& operator = (const set &other)
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

	/*	Iterators	*/
	iterator				begin() 			{return iterator(&_t).begin();}
	const_iterator			begin()		const	{return const_iterator(&_t).begin();};
	iterator				end()				{return iterator(&_t).end();}
	const_iterator			end()		const	{return const_iterator(&_t).end();};
	reverse_iterator		rbegin() 			{return reverse_iterator(&_t).begin();};
	const_reverse_iterator	rbegin()	const	{return const_reverse_iterator(&_t).begin();};
	reverse_iterator		rend()				{return reverse_iterator(&_t).end();};
	const_reverse_iterator	rend()		const	{return const_reverse_iterator(&_t).end();};

	/*	Capacity	*/
	bool		empty()		const	{if (_t.size() == 0) return true; return false;}	/* Check si le container est vide									*/
	size_type	size()		const	{return _t.size();}									/* Retourne, en `size_type`, le nombre d'objet dans le container	*/
	size_type	max_size()	const	{return _alloc.max_size() / 10;}					/* Retourne, en `size_type`, le nb max d'objet dans le container	*/
												//	^~~~ PUE SA MERE DEMANDER A CLODAGH

	/*	Modifiers	*/
	void	clear() {_t.clear();}	/* Efface tous les elements du container, le container redeviens comme si on appelais son constructeur par defaut	*/

	// a change r en consequence de la fcn den dessous
	ft::pair<iterator, bool>	insert(const value_type* value)	/* Ajoute une valeur au container avec la valeur pointee en paramettre					*/
	{
		ft::pair<iterator, bool>	p;
		iterator					it;
		iterator					ite;
	
		p.second = _t.add(*value);
		if (p.second)
		{
			for (it = begin(), ite = end(); it != ite; it++)
			{
				if (*it == *value)
				{
					p.first = it;
					break;
				}
			}
		}
		return p;
	}
	
	ft::pair<iterator, bool>	insert(const value_type& value)	/* Ajoute une valeur au container avec la valeur en paramettre							*/
	{
		iterator	save(&_t);
		iterator	it = begin();
		iterator	ite = end();
		bool		second;
	
		second = _t.add(value);
		if (second)
			save = find(value);
		ft::pair<iterator, bool>	p(save, second);
		return p;
	}

	template <class InputIt>
	void	insert(InputIt first, InputIt last)	/* Ajoute des valeurs au containers avec la range d'iterateurs	*/
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

	iterator	erase(iterator pos)		/* Enleve un element du container avec sa position grace a l'iterateur	*/
	{
		node<Key>	*nd = _t.search(*pos);
		if (nd)
			_t.del(*pos);
		return iterator(&_t);
	}
	
	size_type	erase(const Key &key)	/* Enleve un element du container avec sa valeur	*/
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
	
		// std::cout << "dans erase" << std::endl;
		//getwchar();
		if (first == begin() && last == end())
		{
			clear();
			std::cout << "LLLLLLLLLLLLLLLLLLLfin erase tout" << std::endl;
			return begin();
		}
	
		// std::cout << "avant lop *" << std::endl;
		//getwchar();
		// std::cout << "avant le for : [" << *first << "] [" << *last << "]" <<  std::endl;
		//getwchar();
		for (; first != last;)
		{
			// //getwchar();
			if (*first == *--last)
				break;
			save = ++first;
			// // std::cout << "apres delete de [" << *first << "] :" << std::endl;
			_t.del(*--first);
			// _t.print();
			// // std::cout << "-------------------------" << std::endl;
			first = save;
		}
		// std::cout << "fin erase" << std::endl;
		//getwchar();
		return iterator(&_t);
	}

	void	swap(set &other)	/* On verra	*/
	{
		set	tmp(other);
	
		other = *this;
		*this = tmp;
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
	
		p.first = find(key);
		p.second = find(key);
		p.second++;
	
		return p;
	}

	ft::pair<const_iterator, const_iterator>	equal_range(const Key &key)	const
	{
		ft::pair<const_iterator, const_iterator>	p;
	
		p.first = find(key);
		p.second = find(key);
		p.second++;
	
		return p;
	}
	
	iterator	lower_bound(const Key &key)
	{
		Key	var = key;
		node<Key>	*ptr;
		if (var > _t.max()->value)
			return end();
		while ((ptr = _t.search(var)) != 0)
		{
			var++;
		}
		return find(var);
	}
	
	const_iterator	lower_bound(const Key &key)	const
	{
		Key	var = key;
		node<Key>	*ptr;
		if (var > _t.max()->value)
			return end();
		while ((ptr = _t.search(var)) != 0)
		{
			var++;
		}
		return find(var);
	}
	
	iterator	upper_bound(const Key &key)
	{
		Key	var = key;
		node<Key>	*ptr;
		var++;
		if (var > _t.max()->value)
			return end();
		while ((ptr = _t.search(var)) != 0)
		{
			var++;
		}
		return find(var);
	}
	
	const_iterator	upper_bound(const Key &key)	const
	{
		Key	var = key;
		node<Key>	*ptr;
		var++;
		if (var > _t.max()->value)
			return end();
		while ((ptr = _t.search(var)) != 0)
		{
			var++;
		}
		return find(var);
	}

	/*	Observers	*/
	key_compare	key_comp()	const	{return _comp;};
	
	value_compare	value_comp()	const {return _comp;};

friend bool	operator ==	(const ft::set<Key, Compare, Allocator> &lhs,
					const ft::set<Key, Compare, Allocator> &rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

friend bool	operator !=	(const ft::set<Key, Compare, Allocator> &lhs,
					const ft::set<Key, Compare, Allocator> &rhs)
{
	return (!(lhs == rhs));
}

friend bool	operator <	(const ft::set<Key, Compare, Allocator> &lhs,
					const ft::set<Key, Compare, Allocator> &rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	
}

friend bool	operator <=	(const ft::set<Key, Compare, Allocator> &lhs,
					const ft::set<Key, Compare, Allocator> &rhs)
{
	return (!(rhs < lhs));	
}

friend bool	operator >	(const ft::set<Key, Compare, Allocator> &lhs,
					const ft::set<Key, Compare, Allocator> &rhs)
{
	return (rhs < lhs);
}

friend bool	operator >=	(const ft::set<Key, Compare, Allocator> &lhs,
					const ft::set<Key, Compare, Allocator> &rhs)
{
	return (!(lhs < rhs));
}
// A REMETTRE EN PRIVE PLUS TARD
//private:
	Compare								_comp;
	Allocator							_alloc;
	ft::tree<Key, Compare>	_t;
};

// template <class Key, class Compare, class Allocator>
// bool	operator <= (const ft::set<Key, Compare, Allocator> &lhs,
// 					const ft::set<Key, Compare, Allocator> &rhs);

// template <class Key, class Compare, class Allocator>
// bool	operator >	(const ft::set<Key, Compare, Allocator> &lhs,
// 					const ft::set<Key, Compare, Allocator> &rhs);

// template <class Key, class Compare, class Allocator>
// bool	operator >=	(const ft::set<Key, Compare, Allocator> &lhs,
// 					const ft::set<Key, Compare, Allocator> &rhs);

// template <class Key, class Compare, class Allocator>
// void	swap(const ft::set<Key, Compare, Allocator> &lhs,
// 			const ft::set<Key, Compare, Allocator> &rhs);
}

#endif