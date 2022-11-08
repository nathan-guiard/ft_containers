/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:15:13 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/04 18:35:19 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_SET_HPP
#define		FT_SET_HPP

#include 	<functional> //a surement enlever
#include	<memory>
#include	<set>	//a enlever
#include	"rb_tree.hpp"
#include	"iterator_traits.hpp"

namespace ft
{

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set
{
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
	};

	~set() {};

	set& operator = (const set &other)
	{
		this->_t = other._t;
		this->_comp = other._comp;
		this->_alloc = other._alloc;
	
		return *this;
	};

	allocator_type	get_allocator()	const
	{
		return _alloc;
	};

	/*	Iterators	*/
	struct	SetIterator : public ft::iterator_traits<std::bidirectional_iterator_tag, Key>
	{
	public:	
		reference operator*()	const
		{
			return curr->value;
		};
		pointer operator->()	const
		{
			return curr;
		};

		SetIterator &operator++()
		{
			curr = _t.next(curr);

			return *this;
		};

		SetIterator	operator++(int)
		{
			SetIterator tmp;
			
			tmp = *this;
			++*this;
			return tmp;
		};
		SetIterator	&operator--();
		SetIterator	operator--(int);
	
		// bool	operator == (const SetIterator &x,
							// const SetIterator &y);

	private:
		node<Key>	*curr;
		bool		_is_end;
	};
	
	template <class SetIterator = ft::set<Key, Compare, Allocator>::iterator>
	friend bool	operator != (const SetIterator &x,
							const SetIterator &y);

	// template <class Key>
	class	SetRIterator : public ft::iterator_traits<std::bidirectional_iterator_tag, Key>
	{
	public:
		SetRIterator();
		// explicit	SetRIterator();
		~SetRIterator();
	
		Key	&operator*()	const;
		Key	*operator->()	const;

		SetRIterator	&operator++();
		SetRIterator	operator++(int);
		SetRIterator	&operator--();
		SetRIterator	operator--(int);
	
		// friend bool	operator == (const SetRIterator &x,
		// 						const SetRIterator &y);
		// friend bool	operator != (const SetRIterator &x,
		// 						const SetRIterator &y);

	private:
		Key	curr;
	};

	iterator		begin();			// retourne un `iterator` sur le debut
	const_iterator	begin()		const;	// retourne un `const_iterator` sur le debut
	iterator		end();				// retourne un `iterator` sur l'end
	const_iterator	end()		const;	// retourne un `const_iterator` sur l'end
	iterator		rbegin();			// retourne un `reverse_iterator` sur le debut
	const_iterator	rbegin()	const;	// retourne un `reverse_const_iterator` sur le debut
	iterator		rend();				// retourne un `reverse_iterator` sur l'end
	const_iterator	rend()		const;	// retourne un `reverse_const_iterator` sur l'end

	/*	Capacity	*/
	bool		empty()		const;	// Check si le container est vide
	size_type	size()		const;	// Retourne, en `size_type`, le nombre d'objet dans le container
	size_type	max_size()	const;	// Retourne, en `size_type`, le nb max d'objet dans le container

	/*	Modifiers	*/
	void	clear();
	std::pair<iterator, bool>	insert(const value_type* value);	// Efface tous les elements du container, comme si on appelais le constructeur par defaut
	std::pair<iterator, bool>	insert(const value_type& value);	// Ajoute une valeur au container avec la valeur en paramettres
	template <class InputIt>
	void	insert(InputIt first, InputIt last);	// Ajoute des valeurs au containers avec la range d'iterateurs

	iterator	erase(iterator pos);	// Enleve un element du container avec sa position grace a l'iterateur
	size_type	erase(const Key &key);	// Enleve un element du container avec sa valeur

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
// private:
	Compare			_comp;
	Allocator		_alloc;
	ft::tree<Key>	_t;
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