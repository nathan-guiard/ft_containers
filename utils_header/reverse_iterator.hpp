/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:28:00 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/18 16:38:08 by nguiard          ###   ########.fr       */
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

	template <class iter>
	reverse_iterator(const iter &c): _b(c.base()) {}
	reverse_iterator(const Iterator &c): _b(c) {}

	reverse_iterator	&operator = (const reverse_iterator &c)
	{
		_b = c.base();
		return *this;
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
	
	reverse_iterator	rbegin()
	{
		_b = _b.end();
		return *this;
	}

	reverse_iterator	rend()
	{
		_b = _b.begin();
		return *this;
	}
	
	bool operator == (const reverse_iterator &y)	const
	{
		return (this->_b == y._b);
	}
	
	bool operator != (const reverse_iterator &y)	const
	{
		return (!(*this == y));
	}
	
	bool operator <  (const reverse_iterator &y)	const
	{
		return (_b < y._b);
	}

private:
	Iterator	_b;
};

}

#endif