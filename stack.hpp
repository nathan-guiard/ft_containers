/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:13:32 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/23 14:17:39 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <cstddef>
#include "vector.hpp"

namespace ft
{

template <class T, class Container = ft::vector<T> > // a changer par vector
class stack
{
public:
	typedef	Container							container_type;
	typedef	typename Container::value_type		value_type;
	typedef	typename Container::size_type		size_type;
	typedef	typename Container::reference		reference;
	typedef	typename Container::const_reference	const_reference;

	explicit stack(const Container &c = Container()) {this->c = c;}
	stack(const stack &other) {*this = other;}
	~stack() {}

	stack	&operator = (const stack &other) {this->c = other.c; return *this;}

	/*	ELEMENT ACCES	*/
	reference top()					{return c.back();}
	const_reference	top()	const	{return c.back();}

	/*	CAPACITY		*/
	bool		empty()	const		{return c.empty();}
	size_type	size()	const		{return c.size();}

	/*	MODIFIERS		*/
	void	push(const value_type &value)	{c.push_back(value);}
	void	pop()							{c.pop_back();};

	bool operator == (const stack &b)	const
	{
		return (c == b.c);
	}


	bool operator != (const stack &b)	const
	{
		return (c != b.c);
	}


	bool operator <  (const stack &b)	const
	{
		return (c < b.c);
	}


	bool operator <= (const stack &b)	const
	{
		return (c <= b.c);
	}


	bool operator >  (const stack &b)	const
	{
		return (c > b.c);
	}


	bool operator >= (const stack &b)	const
	{
		return (c >= b.c);
	}

protected:
	Container	c;
}; // fin de la class stack



} //fin de lu namespace ft

#endif
