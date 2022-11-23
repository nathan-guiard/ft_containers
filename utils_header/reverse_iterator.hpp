/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:28:00 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/23 11:44:12 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iterator, typename size_type = std::ptrdiff_t>
class reverse_iterator
{
public:
	typedef	typename Iterator::value_type	value_type;
	typedef	typename Iterator::distance		distance;

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
		--tmp;
		return *tmp;
	}
	
	value_type	*operator->()	const
	{
		return	&(this->operator*());
	}

	reverse_iterator	&operator++()
	{
		--_b;
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
		++_b;
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
		return (y._b < _b);
	}
	
	bool operator > (const reverse_iterator &y)		const
	{
		return (y._b > _b);
	}

	bool operator >= (const reverse_iterator &y)		const
	{
		return (y._b >= _b);
	}

	bool operator <= (const reverse_iterator &y)		const
	{
		return (y._b <= _b);
	}

	reverse_iterator	operator - (size_type x)	const
	{
		return (reverse_iterator(_b + x));
	}

	distance	operator - (const reverse_iterator &x)	const
	{
		return (_b - x.base());
	}

	reverse_iterator	operator + (size_type x)	const
	{
		return (reverse_iterator(_b - x));
	}

	distance	operator + (const reverse_iterator &x)	const
	{
		return (_b + x.base());
	}

	reverse_iterator	operator -= (size_type x)
	{
		_b += x;
		return *this;
	}

	reverse_iterator	operator += (size_type x)
	{
		_b -= x;
		return *this;
	}
	
	value_type	&operator[](size_type x)
	{
		return *(*this + x);
	}

private:
	Iterator	_b;
};

template <class iterator, typename size_type>
reverse_iterator<iterator, size_type> operator + (int i,
	const reverse_iterator<iterator, size_type> b)
{
	return b.base() - i;
}

template <class iterator, typename size_type>
reverse_iterator<iterator, size_type> operator - (int i,
	const reverse_iterator<iterator, size_type> b)
{
	return b.base() + i;
}

template <class ita, class itb>
typename reverse_iterator<ita>::distance	operator - (const reverse_iterator<ita> &a,
											const reverse_iterator<itb> &b)
{
	return (b.base() - a.base());
}

template <class ita, class itb>
typename reverse_iterator<ita>::distance	operator + (const reverse_iterator<ita> &a,
											const reverse_iterator<itb> &b)
{
	return (b.base() + a.base());
}

}
// random access tag
#endif