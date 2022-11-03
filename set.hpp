/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:15:13 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/03 12:41:40 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_SET_HPP
#define		FT_SET_HPP

#include 	<functional> //a surement enlever
#include	<memory>
#include	<set>	//a enlever

namespace ft
{

template <
	class Key,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<Key> >
class set
{
public:
	typedef	key_type				Key;
	typedef	value_type				Key;
	typedef	size_type				std::size_t;
	typedef	difference_type			std::ptrdiff_t;
	typedef	key_compare				Compare;
	typedef	value_compare			Compare;
	typedef	reference				value_type &;
	typedef	const_reference 		const value_type &;
	typedef	pointer					Allocator::pointer;
	typedef	const_pointer			Allocator::const_pointer;
	typedef	iterator				set::SetIterator;
	typedef	const_iterator			const set::SetIterator;
	typedef	reverse_iterator		set::SetRIterator;
	typedef	const_reverse_iterator	const set::SetRIterator;

	/*	MEMBER FUNCTIONS			*/
	/*	Constructors/Destructor		*/
	set() {};
	explicit set(const Compare &comp,
		const Allocator &alloc = Allocator());

	template <class InputIt>
	set(InputIt first, InputIt last,
		const Compare &comp = Compare(),
		const Allocator &alloc = Allocator());

	~set() {};

	set& operator = (const set &other);

	allocator_type	get_allocator()	const;

	/*	Iterators	*/
	template <typename Key>
	class	SetIterator
	{
	public:
		SetIterator();
		explicit	SetIterator()
		~SetIterator();
	
		Key	&operator*()	const;
		Key	*operator->()	const;

		SetIterator<Key>	&operator++();
		SetIterator<Key>	operator++(int);
		SetIterator<Key>	&operator--();
		SetIterator<Key>	operator--(int);
	
		friend bool	operator == (const SetIterator<Key> &x,
								const SetIterator<Key> &y);
		friend bool	operator != (const SetIterator<Key> &x,
								const SetIterator<Key> &y);

	private:
		//node	*curr;
	};

	template <typename Key>
	class	SetRIterator
	{
	public:
		SetRIterator();
		explicit	SetRIterator()
		~SetRIterator();
	
		Key	&operator*()	const;
		Key	*operator->()	const;

		SetRIterator<Key>	&operator++();
		SetRIterator<Key>	operator++(int);
		SetRIterator<Key>	&operator--();
		SetRIterator<Key>	operator--(int);
	
		friend bool	operator == (const SetRIterator<Key> &x,
								const SetRIterator<Key> &y);
		friend bool	operator != (const SetRIterator<Key> &x,
								const SetRIterator<Key> &y);

	private:
		//node	*curr;
	};

	iterator		begin();	// retourne un `iterator` sur le debut
	const_iterator	begin();	// retourne un `const_iterator` sur le debut
	iterator		end();		// retourne un `iterator` sur l'end
	const_iterator	end();		// retourne un `const_iterator` sur l'end
	iterator		rbegin();	// retourne un `reverse_iterator` sur le debut
	const_iterator	rbegin();	// retourne un `reverse_const_iterator` sur le debut
	iterator		rend();		// retourne un `reverse_iterator` sur l'end
	const_iterator	rend();		// retourne un `reverse_const_iterator` sur l'end

	/*	Capacity	*/
	bool		empty()		const;	// Check si le container est vide
	size_type	size()		const;	// Retourne, en `size_type`, le nombre d'objet dans le container
	size_type	max_size()	const;	// Retourne, en `size_type`, le nb max d'objet dans le container

	/*	Modifiers	*/
	void	clear();
	std::pair<iterator, bool>	insert(const value_type* value);	// Efface tous les elements du container, comme si on appelais le constructeur par defaut

	std::pair<iterator, bool> insert( const value_type& value );	// Ajoute une valeur au container avec la valeur en paramettres
	template <class InputIt>
	void	insert(InputIt first, InputIt last);	// Ajoute des valeurs au containers avec la range d'iterateurs

	iterator	erase(iterator pos);	// Enleve un element du container avec sa position grace a l'iterateur
	size_type	erase(const Key &key);	// Enleve un element du container avec sa valeur

	void	swap(set &other);	// 

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