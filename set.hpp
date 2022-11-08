/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:15:13 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/08 12:00:07 by nguiard          ###   ########.fr       */
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

namespace ft
{

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set
{
// private: // a remettre PV
public:
	Compare			_comp;
	Allocator		_alloc;
	ft::tree<Key>	_t;

public:
	class SetIterator;
	class SetRIterator;

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
	typedef	const set::SetIterator				const_iterator;
	typedef	set::SetRIterator					reverse_iterator;
	typedef	const set::SetRIterator				const_reverse_iterator;

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
		
		reference operator*()	const
		{
			Key var = Key();
			Key &ref = var;
			if (_curr)
				return _curr->value;
			return ref;
		}
	
		pointer operator->()	const	{return _curr;}

		SetIterator &operator++()
		{
			if (!_curr || !_it_tree)
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

		bool	operator == (const SetIterator &y)
		{
			if (this->_curr == y._curr)
				return true;
			return false;
		}
		bool	operator != (const SetIterator &y)
		{
			if (this->_curr != y._curr)
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
		SetRIterator(): _curr(), _is_end(false) { _it_tree = 0;};
		SetRIterator(const tree<Key>	*tr): _curr(tr->max()), _is_end(false) { _it_tree = tr;};
		
		reference operator*()	const
		{
			Key var = Key();
			Key &ref = var;
			if (_curr)
				return _curr->value;
			return ref;
		}
	
		pointer operator->()	const	{return _curr;}

		SetRIterator &operator++()
		{
			if (!_curr || !_it_tree)
				return *this;
			_curr = _it_tree->prev(_curr);
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
			if (!_it_tree)
				return *this;
			if (_is_end)
			{
				_curr = _it_tree->min();
				_is_end = false;
			}
			else
				_curr = _it_tree->next(_curr);
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
			_curr = _it_tree->max();
			if (!_curr)
				_is_end = true;
		
			return *this;
		}
		
		reverse_iterator	end()
		{
			_curr = 0;
			_is_end = true;
		
			return *this;
		}

		bool	operator == (const SetRIterator &y)
		{
			if (this->_curr == y._curr)
				return true;
			return false;
		}
		bool	operator != (const SetRIterator &y)
		{
			if (this->_curr != y._curr)
				return true;
			return false;
		}

	private:
		const tree<Key>	*_it_tree;
		node<Key>		*_curr;
		bool			_is_end;
	};

	iterator				begin() 			{return SetIterator(&_t).begin();};		// retourne un `iterator` sur le debut
	const_iterator			begin()		const	{return SetIterator(&_t).begin();};		// retourne un `const_iterator` sur le debut
	iterator				end()				{return SetIterator(&_t).end();};		// retourne un `iterator` sur l'end
	const_iterator			end()		const	{return SetIterator(&_t).end();};		// retourne un `const_iterator` sur l'end
	reverse_iterator		rbegin() 			{return SetRIterator(&_t).begin();};	// retourne un `reverse_iterator` sur le debut
	const_reverse_iterator	rbegin()	const	{return SetRIterator(&_t).begin();};	// retourne un `const_reverse_iterator` sur le debut
	reverse_iterator		rend()				{return SetRIterator(&_t).end();};		// retourne un `reverse_iterator` sur l'end
	const_reverse_iterator	rend()		const	{return SetRIterator(&_t).end();};		// retourne un `const_reverse_iterator` sur l'end

	/*	Capacity	*/
	bool		empty()		const {if (_t.size() == 0) return true; return false;}	// Check si le container est vide
	size_type	size()		const;	// Retourne, en `size_type`, le nombre d'objet dans le container
	size_type	max_size()	const;	// Retourne, en `size_type`, le nb max d'objet dans le container

	/*	Modifiers	*/
	void	clear();	// Efface tous les elements du container, le container redeviens comme si on appelais son constructeur par defaut
	
	std::pair<iterator, bool>	insert(const value_type* value);	// Ajoute une valeur au container avec la valeur pointee en paramettre
	std::pair<iterator, bool>	insert(const value_type& value);	// Ajoute une valeur au container avec la valeur en paramettre
	// {
	// 	std::pair<iterator, bool>	pair;
	
	// }
	template <class InputIt>
	void	insert(InputIt first, InputIt last);	// Ajoute des valeurs au containers avec la range d'iterateurs

	iterator	erase(iterator pos);	// Enleve un element du container avec sa position grace a l'iterateur
	size_type	erase(const Key &key)	// Enleve un element du container avec sa valeur
	{
		node<Key>	*nd = _t.search(key);
		if (!nd)
			return 0;
		_t.del(key);
		return 1;
	}
	void	swap(set &other);	// On verra

	/*	Look up		*/
	size_type		count(const Key &key)	const;
	iterator		find(const Key &key);
	const_iterator	find(const Key &key)	const;
	std::pair<iterator, iterator>	equal_range(const Key &key);
	std::pair<const_iterator, const_iterator>	equal_range(const Key &key)	const;
	iterator	lower_bound(const Key &key);
	const_iterator	lower_bound(const Key &key)	const;
	iterator	upper_bound(const Key &key);
	const_iterator	upper_bound(const Key &key)	const;

	/*	Observers	*/
	key_compare	key_comp()	const;
	value_compare	value_comp()	const;

// A REMETTRE EN PRIVE PLUS TARD
};

template <class Key, class Compare, class Alloc>
bool	operator ==	(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs);

template <class Key, class Compare, class Alloc>
bool	operator !=	(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs);

template <class Key, class Compare, class Alloc>
bool	operator <	(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs);

template <class Key, class Compare, class Alloc>
bool	operator <= (const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs);

template <class Key, class Compare, class Alloc>
bool	operator >	(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs);

template <class Key, class Compare, class Alloc>
bool	operator >=	(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs);

template <class Key, class Compare, class Alloc>
void	swap(const ft::set<Key, Compare, Alloc> &lhs,
			const ft::set<Key, Compare, Alloc> &rhs);
}

#endif