/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:15:13 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/09 14:55:03 by nguiard          ###   ########.fr       */
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
	class SetIterator;
	class SetConstIt;
	class SetRIterator;
	class SetConstRIt;

	typedef	Key									key_type;
	typedef	Key									value_type;
	typedef	std::size_t							size_type;
	typedef	std::ptrdiff_t 						difference_type;
	typedef	Compare 							key_compare;
	typedef	Compare 							value_compare;
	typedef	Allocator							allocator_type;
	typedef	value_type &						reference;
	typedef	const value_type &					const_reference;
	typedef	typename Allocator::pointer			pointer;
	typedef	typename Allocator::const_pointer	const_pointer;
	typedef	set::SetIterator					iterator;
	typedef	set::SetConstIt						const_iterator;
	typedef	set::SetRIterator					reverse_iterator;
	typedef	SetConstRIt							const_reverse_iterator;

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
	struct	SetIterator : public ft::iterator_traits<std::bidirectional_iterator_tag, Key>
	{
	public:	
		SetIterator(): _curr(), _is_end(false) { _it_tree = 0;};
		SetIterator(const tree<Key>	*tr): _curr(tr->min()), _is_end(false) { _it_tree = tr;};
		SetIterator(const SetIterator &c): _it_tree(c._it_tree), _curr(c._curr), _is_end(c._is_end) {};
		SetIterator(const SetConstIt &c): _it_tree(c.get_tree()), _curr(c.get_curr()), _is_end(c.get_isend()) {};

		const tree<Key>	*get_tree()	const {return _it_tree;};

		node<Key>	*get_curr() const {return _curr;};
	
		bool	get_isend()	const	{return _is_end;};

		const_reference operator*()	const
		{
			Key var = Key();
			Key &ref = var;
			if (_curr)
				return _curr->value;
			return ref;
		}
	
		const_pointer operator->()	const	{return &_curr->value;}

		SetIterator &operator++()
		{
			if (!_curr || !_it_tree || _it_tree->size() == 0)
				return *this;
			_curr = _it_tree->next(_curr);
			return *this;
		}

		SetIterator	operator++(int)
		{
			SetIterator tmp;
			
			tmp = *this;
			++*this;
			return tmp;
		}
		
		SetIterator	&operator--()
		{
			if (!_it_tree)
				return *this;
			if (_is_end)
			{
				_curr = _it_tree->max();
				_is_end = false;
			}
			else
				_curr = _it_tree->prev(_curr);
			return *this;
		}

		SetIterator	operator--(int)
		{
			SetIterator tmp;
			
			tmp = *this;
			--*this;
			return tmp;
		}

		iterator	begin()
		{
			_curr = _it_tree->min();
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

		bool	operator == (const SetIterator &y)	const
		{
			if (this->_curr == y._curr)
				return true;
			return false;
		}
		bool	operator != (const SetIterator &y)	const
		{
			if (this->_curr != y._curr)
				return true;
			return false;
		}
		bool	operator < (const SetIterator &y)	const
		{
			if (_curr->value < y._curr->value)
				return true;
			return false;
		}

	protected:
		const tree<Key>	*_it_tree;
		node<Key>		*_curr;
		bool			_is_end;
	};

	struct	SetConstIt : public ft::iterator_traits<std::bidirectional_iterator_tag, Key>
	{
	public:	
		SetConstIt(): _curr(), _is_end(false) { _it_tree = 0;};
		SetConstIt(const tree<Key>	*tr):	_curr(tr->min()), _is_end(false) { _it_tree = tr;};
		SetConstIt(const SetConstIt &c):	_it_tree(c._it_tree), _curr(c._curr), _is_end(c._is_end) {};
		SetConstIt(const SetIterator &c):	_it_tree(c.get_tree()), _curr(c.get_curr()), _is_end(c.get_isend()) {};

		const tree<Key>	*get_tree()	const {return _it_tree;};

		node<Key>	*get_curr() const {return _curr;};
	
		bool	get_isend()	const	{return _is_end;};

		const_reference operator*()	const
		{
			Key var = Key();
			Key &ref = var;
			if (_curr)
				return _curr->value;
			return ref;
		}
	
		const_pointer operator->()	const	{return &_curr->value;}

		SetConstIt &operator++()
		{
			if (!_curr || !_it_tree || _it_tree->size() == 0)
				return *this;
			_curr = _it_tree->next(_curr);
			return *this;
		}

		SetConstIt	operator++(int)
		{
			SetConstIt tmp;
			
			tmp = *this;
			++*this;
			return tmp;
		}
		
		SetConstIt	&operator--()
		{
			if (!_it_tree)
				return *this;
			if (_is_end)
			{
				_curr = _it_tree->max();
				_is_end = false;
			}
			else
				_curr = _it_tree->prev(_curr);
			return *this;
		}

		SetConstIt	operator--(int)
		{
			SetConstIt tmp;
			
			tmp = *this;
			--*this;
			return tmp;
		}

		const_iterator	begin()
		{
			_curr = _it_tree->min();
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

		bool	operator == (const SetConstIt &y)	const
		{
			if (this->_curr == y._curr)
				return true;
			return false;
		}

		bool	operator != (const SetConstIt &y)	const
		{
			if (this->_curr != y._curr)
				return true;
			return false;
		}
		bool	operator < (const SetConstIt &y)	const
		{
			if (_curr->value < y._curr->value)
				return true;
			return false;
		}

	private:
		const tree<Key>	*_it_tree;
		node<Key>		*_curr;
		bool			_is_end;
	};

	struct	SetRIterator : public ft::iterator_traits<std::bidirectional_iterator_tag, Key>
	{
	public:	
		SetRIterator(): _base() {};
		SetRIterator(const tree<Key> *tr):	_base(tr)	{};
		SetRIterator(const SetIterator &c): _base(c)	{};
		SetRIterator(const SetConstIt &c):	_base(c)	{};

		iterator	base()	const
		{
			return _base;
		}

		const_reference operator*()	const
		{
			return *_base;
		}
	
		const_pointer operator->()	const	{return &_base.get_curr()->value;}

		SetRIterator &operator++()
		{
			_base--;
			return *this;
		}

		SetRIterator	operator++(int)
		{
			SetRIterator tmp;
			
			tmp = *this;
			++*this;
			return tmp;
		}
		
		SetRIterator	&operator--()
		{
			_base++;
			return *this;
		}

		SetRIterator	operator--(int)
		{
			SetRIterator tmp;
			
			tmp = *this;
			--*this;
			return tmp;
		}

		reverse_iterator	begin()
		{
			return _base.end()--;
		}
		
		reverse_iterator	end()
		{
			return _base.begin()--;
		}

		bool	operator == (const SetRIterator &y)
		{
			if (*_base == *y._base)
				return true;
			return false;
		}
		bool	operator != (const SetRIterator &y)
		{
			if (*_base != *y._base)
				return true;
			return false;
		}
		bool	operator < (const SetRIterator &y)	const
		{
			if (*_base > *y._base)
				return true;
			return false;
		}

	private:
		iterator		_base;
	};

	struct	SetConstRIt : public ft::iterator_traits<std::bidirectional_iterator_tag, Key>
	{
	public:	
		SetConstRIt(): _base() {};
		SetConstRIt(const tree<Key> *tr):	_base(tr)	{};
		SetConstRIt(const SetIterator &c):	_base(c)	{};
		SetConstRIt(const SetConstIt &c):	_base(c)	{};
		SetConstRIt(const SetRIterator &c):	_base(c.base())	{};

		const_iterator	base()	const
		{
			return _base;
		}

		const_reference operator*()	const
		{
			return *_base;
		}
	
		const_pointer operator->()	const	{return &_base.get_curr()->value;}

		SetConstRIt &operator++()
		{
			_base--;
			return *this;
		}

		SetConstRIt	operator++(int)
		{
			SetConstRIt tmp;
			
			tmp = *this;
			++*this;
			return tmp;
		}
		
		SetConstRIt	&operator--()
		{
			_base++;
			return *this;
		}

		SetConstRIt	operator--(int)
		{
			SetConstRIt tmp;
			
			tmp = *this;
			--*this;
			return tmp;
		}

		const_reverse_iterator	begin()
		{
			return _base.end()--;
		}
		
		const_reverse_iterator	end()
		{
			return _base.begin()--;
		}

		bool	operator == (const SetConstRIt &y)
		{
			if (*_base == *y._base)
				return true;
			return false;
		}
		bool	operator != (const SetConstRIt &y)
		{
			if (*_base != *y._base)
				return true;
			return false;
		}
		bool	operator < (const SetConstRIt &y)	const
		{
			if (*_base > *y._base)
				return true;
			return false;
		}

	private:
		iterator		_base;
	};

	iterator				begin() 			{return iterator(&_t).begin();};				/* retourne un `iterator` sur le debut					*/
	const_iterator			begin()		const	{return const_iterator(&_t).begin();};			/* retourne un `const_iterator` sur le debut			*/
	iterator				end()				{return iterator(&_t).end();};					/* retourne un `iterator` sur l'end						*/
	const_iterator			end()		const	{return const_iterator(&_t).end();};			/* retourne un `const_iterator` sur l'end				*/
	reverse_iterator		rbegin() 			{return reverse_iterator(&_t).begin();};		/* retourne un `reverse_iterator` sur le debut			*/
	const_reverse_iterator	rbegin()	const	{return const_reverse_iterator(&_t).begin();};	/* retourne un `const_reverse_iterator` sur le debut	*/
	reverse_iterator		rend()				{return reverse_iterator(&_t).end();};			/* retourne un `reverse_iterator` sur l'end				*/
	const_reverse_iterator	rend()		const	{return const_reverse_iterator(&_t).end();};	/* retourne un `const_reverse_iterator` sur l'end		*/

	/*	Capacity	*/
	bool		empty()		const	{if (_t.size() == 0) return true; return false;}	/* Check si le container est vide									*/
	size_type	size()		const	{return _t.size();}									/* Retourne, en `size_type`, le nombre d'objet dans le container	*/
	size_type	max_size()	const	{return _alloc.max_size() / 10;}					/* Retourne, en `size_type`, le nb max d'objet dans le container	*/
												//	^~~~ PUE SA MERE DEMANDER A CLODAGH

	/*	Modifiers	*/
	void	clear() {_t.clear();};	/* Efface tous les elements du container, le container redeviens comme si on appelais son constructeur par defaut	*/

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
		ft::pair<iterator, bool>	p;
		iterator					it;
		iterator					ite;
	
		p.second = _t.add(value);
		if (p.second)
		{
			for (it = begin(), ite = end(); it != ite; it++)
			{
				if (*it == value)
				{
					p.first = it;
					break;
				}
			}
		}
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
		return iterator();
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
		for (; first != last; first++)
			_t.del(*first);
		return iterator();
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

// template <class Key, class Compare, class Alloc>
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
	Compare			_comp;
	Allocator		_alloc;
	ft::tree<Key>	_t;
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