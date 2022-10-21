/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:27:19 by nguiard           #+#    #+#             */
/*   Updated: 2022/10/21 18:00:50 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_MAP_HPP
#define		FT_MAP_HPP

#include	<functional>
#include	<memory>
#include	<map> // a enlever lol
#include	<iterator>

namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > > // std::pair a changer?
class	map
{
public:
	/*	MEMBER TYPES			*/
	typedef key_type		Key;
	typedef mapped_type		T;
	typedef value_type		std::pair<const Key, T> // std::pair a changer?
	typedef size_type		std::size_t;
	typedef difference_type	std::ptrdiff_t;
	typedef key_compare		Compare;
	typedef allocator_type	Allocator;
	typedef reference		value_type&;
	typedef const_reference	const value_type&;
	typedef pointer			Allocator::pointer;
	typedef const_pointer	Allocator::const_pointer;
	// typedef iterator		
	// typedef const_iterator
	// typedef reverse_iterator
	// typedef const_reverse_iterator

	/*	MEMBER FUNCTIONS		*/
	map(); //	Surement plus a faire
	~map(); //	Surement plus a faire

	map	&operator = (const map &other);
	
	allocator_type get_allocator() const;

	/*	Element access			*/
	
	T			&at(const Key &key);
	const T		&at(const Key& key) const;
	T			&operator[](const Key& key);

	/*	Iterators				*/

	/*	Capacity				*/
	bool		empty()		const;
	size_type	size()		const;
	size_type	max_size()	const;

	/*	Modifiers				*/
	void						clear();
	std::pair<iterator, bool>	insert(const value_type &value);
	iterator					erase(iterator pos);
	iterator					erase(iterator first, iterator last);
	size_type					erase(const Key& key);
	void						swap(map& other);

	/*	Lookup					*/
	size_type									count(const Key& key)	const;
	iterator									find(const Key& key);
	const_iterator								find(const Key& key)	const;
	std::pair<iterator,iterator>				equal_range(const Key& key);
	std::pair<const_iterator,const_iterator>	equal_range(const Key& key) const;
	iterator									lower_bound(const Key& key);
	const_iterator								lower_bound(const Key& key) const;
	iterator									upper_bound(const Key& key);
	const_iterator								upper_bound(const Key& key) const;

	/*	Observers				*/
	key_compare				key_comp() const;
	value_compare			value_comp() const;

	class value_compare // go voler celle de la std
	{
	public:
		/*	Member type			*/
		typedef	result_type			bool;
		typedef	first_argument_type	value_type;
		typedef	last_argument_type	value_type;

		value_compare(Compare c): comp(c) {};

		bool	operator()(const value_type& x, const value_type& y) const
		{
			return comp(__x.first, __y.first);
		}

	protected:
		Compare	comp;
	};

	/*	Comparasion operators	*/
	template<class Key, class T, class Compare, class Alloc>
	bool	operator ==	(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool	operator !=	(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool	operator <	(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool	operator <=	(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool	operator >	(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool	operator >=	(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
	
	template< class Key, class T, class Compare, class Alloc >
	void	swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs);
};

}

#endif