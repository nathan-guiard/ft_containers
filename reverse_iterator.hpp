/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:28:00 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/16 11:10:13 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iterator>
class reverse_iterator
{
public:
	typedef	typename Iterator::value_type	value_type;

	reverse_iterator(): _b() {};
	reverse_iterator(const reverse_iterator &c): _b(c.base()) {}

	reverse_iterator	&operator = (const reverse_iterator &c)
	{
		_b = c.b();
	}

	Iterator	base()	const	{return _b;}

	value_type	&operator*()	const
	{
		Iterator	tmp(_b);
		tmp--;
		return *tmp;
	}
	
	value_type	*operator->()	const
	{
		return	&(this->operator*());
	}

	reverse_iterator	&operator++()
	{
		_b--;
		return *this;
	}

	reverse_iterator	operator++(int)
	{
			reverse_iterator	tmp;

			tmp = *this;
			++*this;
			return tmp;
	}

	reverse_iterator	&operator--()
	{
		_b++;
		return *this;
	}

	reverse_iterator	operator--(int)
	{
		reverse_iterator	tmp;

		tmp = *this;
		--*this;
		return tmp;
	}
	
	reverse_iterator	begin()
	{
		_b = _b.end();
		return *this;
	}
	
	reverse_iterator	end()
	{
		_b = _b.begin();
		return *this;
	}
	
	bool operator == (const reverse_iterator &y)	const
	{
		return (*this->base() == y.base());
	}
	
	bool operator != (const reverse_iterator &y)	const
	{
		return (!(*this == y));
	}
	
	bool operator <  (const reverse_iterator &y)	const
	{
		return (this->base() < y.base());
	}

private:
	Iterator	_b;
};

}

#endif