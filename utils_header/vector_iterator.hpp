/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:09:32 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/23 10:45:46 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_ITERATOR_HPP
#define FT_VECTOR_ITERATOR_HPP

#include <cstddef>

namespace ft
{

template <class T, typename size_type>
class vector_iterator;

template <class T, typename size_type>
class const_vector_iterator;

template <class T, typename size_type>
class vector_iterator_base
{
public:
	typedef std::bidirectional_iterator_tag	Category;
	typedef T								value_type;
	typedef	std::ptrdiff_t					distance;
	typedef	T &								reference;
	typedef	T *								pointer;

	vector_iterator_base(): _base(0), _curr(0) {}
	vector_iterator_base(const vector_iterator_base &copy):
		_base(copy._base), _curr(copy._curr) {}
	vector_iterator_base(T *ptr, size_type offset):
		_base(ptr), _curr(offset) {}
	~vector_iterator_base() {};

	vector_iterator_base &operator = (const vector_iterator_base &copy)
	{
		_base = copy._base;
		_curr = copy._curr;
		return *this;
	}
	
	distance	operator - (const vector_iterator_base &x)	const
	{
		return (_curr - x._curr);
	}

	distance	operator + (const vector_iterator_base &x)	const
	{
		return (_curr + x._curr);
	}

	vector_iterator_base	operator + (size_type x)	const
	{
		return (vector_iterator_base(_base, _curr + x));
	}

	vector_iterator_base	operator - (size_type x)	const
	{
		return (vector_iterator_base(_base, _curr - x));
	}

	T	&operator[](size_type i)	const
	{
		return _base[i];
	}

	T	&operator*()	const
	{
		return _base[_curr];
	}

	T	*operator->()	const
	{
		return _base + _curr;
	}

	vector_iterator_base	&operator++()
	{
		_curr++;
		return *this;
	}
	
	vector_iterator_base	operator++(int)
	{
		vector_iterator_base	tmp(*this);
	
		++*this;
		return (tmp);
	}

	vector_iterator_base	&operator--()
	{
		_curr--;
		return (*this);
	}

	vector_iterator_base	operator--(int)
	{
		vector_iterator_base	tmp(*this);
	
		--*this;
		return (tmp);
	}

	bool	operator==(const vector_iterator_base &y)	const
	{
		if (_base == y._base)
		{
			if (_curr == y._curr)
				return true;
		}
		return false;
	}

	bool	operator!=(const vector_iterator_base &y)	const
	{
		return (!(*this == y));
	}

	bool	operator<(const vector_iterator_base &y)	const
	{
		if (_curr < y._curr)
			return true;
		return false;
	}

	bool	operator<=(const vector_iterator_base &y)	const
	{
		if (_curr < y._curr || _curr == y._curr)
			return true;
		return false;
	}

	bool	operator>(const vector_iterator_base &y)	const
	{
		if (_curr > y._curr)
			return true;
		return false;
	}

	bool	operator>=(const vector_iterator_base &y)	const
	{
		if (_curr > y._curr || _curr == y._curr)
			return true;
		return false;
	}
	
private:
	T			*_base;
	size_type	_curr;
};

template <class T, typename size_type>
class vector_iterator
{
public:
	typedef std::bidirectional_iterator_tag		Category;
	typedef T									value_type;
	typedef	std::ptrdiff_t						distance;
	typedef	T &									reference;
	typedef	T *									pointer;

	vector_iterator(): _b() {};
	vector_iterator(const vector_iterator &c): _b(c._b) {};
	vector_iterator(const vector_iterator_base<T, size_type> &c): _b(c) {};
	vector_iterator(T *base, size_type offset): _b(base, offset) {};
	~vector_iterator() {}

	vector_iterator_base<T, size_type> base()	const {return _b;}

	vector_iterator &operator = (const vector_iterator &copy)
	{
		_b = copy._b;
		return *this;
	}

	distance	operator - (const const_vector_iterator<T, size_type> &x)	const
	{
		return (_b - x.base());
	}

	distance	operator - (const vector_iterator &x)	const
	{
		return (_b - x._b);
	}

	vector_iterator	operator - (size_type x)	const
	{
		return (_b - x);
	}

	vector_iterator	operator -= (size_type x)
	{
		*this = *this - x;
		return *this;
	}

	distance	operator + (const vector_iterator &x)	const
	{
		return (_b + x._b);
	}

	distance	operator + (const const_vector_iterator<T, size_type> &x)	const
	{
		return (_b + x.base());
	}

	vector_iterator	operator + (size_type x)			const
	{
		return (_b + x);
	}

	vector_iterator	operator += (size_type x)
	{
		*this = *this + x;
		return *this;
	}

	T	&operator[](size_type i)	const
	{
		return _b[i];
	}

	T	&operator*()	const
	{
		return *_b;
	}

	T	*operator->()	const
	{
		return &(operator*());
	}

	vector_iterator	&operator++()
	{
		_b++;
		return *this;
	}
	
	vector_iterator	operator++(int)
	{
		vector_iterator	tmp(_b);
	
		++_b;
		return (tmp);
	}

	vector_iterator	&operator--()
	{
		--_b;
		return *this;
	}

	vector_iterator	operator--(int)
	{
		vector_iterator	tmp(*this);
	
		--*this;
		return (tmp);
	}

	bool	operator==(const vector_iterator &y)	const
	{
		return (_b == y._b);
	}

	bool	operator!=(const vector_iterator &y)	const
	{
		return (_b != y._b);
	}

	bool	operator<(const vector_iterator &y)	const
	{
		return (_b < y._b);
	}

	bool	operator<=(const vector_iterator &y)	const
	{
		return (_b <= y._b);
	}

	bool	operator> (const vector_iterator &y)	const
	{
		return (_b > y._b);
	}

	bool	operator>=(const vector_iterator &y)	const
	{
		return (_b >= y._b);
	}

	/*	OP pour la comparaison avec les iterateurs constants	*/
private:
	vector_iterator_base<T, size_type>	_b;
};



template <class T, typename size_type>
class const_vector_iterator
{
public:
	typedef std::bidirectional_iterator_tag	Category;
	typedef const T							value_type;
	typedef	std::ptrdiff_t					distance;
	typedef	const T &						reference;
	typedef	const T *						pointer;

	const_vector_iterator(): _b() {};
	const_vector_iterator(const vector_iterator<T, size_type> &c): _b(c.base()) {};
	const_vector_iterator(const const_vector_iterator &c): _b(c._b) {};
	const_vector_iterator(const vector_iterator_base<const T, size_type> &c): _b(c) {};
	const_vector_iterator(const vector_iterator_base<T, size_type> &c): _b(c) {};
	const_vector_iterator(T *base, size_type offset): _b(base, offset) {};
	~const_vector_iterator() {}

	vector_iterator_base<T, size_type>	base()	const	{return _b;}

	const_vector_iterator &operator = (const vector_iterator<T, size_type> &copy)
	{
		_b = copy.base();
		return *this;
	}

	distance	operator - (const const_vector_iterator &x)	const
	{
		return (_b - x._b);
	}

	const_vector_iterator	operator - (size_type x)		const
	{
		return (_b - x);
	}
	
	const_vector_iterator	operator -= (size_type x)
	{
		*this = *this - x;
		return *this;
	}

	distance	operator + (const const_vector_iterator &x)	const
	{
		return (_b + x._b);
	}

	const_vector_iterator	operator + (size_type x)		const
	{
		return (_b + x);
	}

	const_vector_iterator	operator += (size_type x)
	{
		*this = *this + x;
		return *this;
	}

	const T	&operator[](size_type i)	const
	{
		return _b[i];
	}

	const T	&operator*()	const
	{
		return *_b;
	}

	const T	*operator->()	const
	{
		return &(operator*());
	}

	const_vector_iterator	&operator++()
	{
		_b++;
		return *this;
	}
	
	const_vector_iterator	operator++(int)
	{
		const_vector_iterator	tmp(_b);
	
		++_b;
		return (tmp);
	}

	const_vector_iterator	&operator--()
	{
		--_b;
		return *this;
	}

	const_vector_iterator	operator--(int)
	{
		const_vector_iterator	tmp(*this);
	
		--*this;
		return (tmp);
	}

	bool	operator==(const const_vector_iterator &y)	const
	{
		return (_b == y._b);
	}

	bool	operator!=(const const_vector_iterator &y)	const
	{
		return (_b != y._b);
	}

	bool	operator<(const const_vector_iterator &y)	const
	{
		return (_b < y._b);
	}

	bool	operator<=(const const_vector_iterator &y)	const
	{
		return (_b <= y._b);
	}

	bool	operator> (const const_vector_iterator &y)	const
	{
		return (_b > y._b);
	}

	bool	operator>=(const const_vector_iterator &y)	const
	{
		return (_b >= y._b);
	}

private:
	vector_iterator_base<T, size_type>	_b;
};

template <class T, typename size_type>
vector_iterator<T, size_type> operator + (int i,
	const vector_iterator<T, size_type> b)
{
	return b.base() + i;
}

template <class T, typename size_type>
vector_iterator<T, size_type> operator - (int i,
	const vector_iterator<T, size_type> b)
{
	return b.base() - i;
}

template <class T, typename size_type>
const_vector_iterator<T, size_type> operator + (int i,
	const const_vector_iterator<T, size_type> b)
{
	return b.base() + i;
}

template <class T, typename size_type>
const_vector_iterator<T, size_type> operator - (int i,
	const const_vector_iterator<T, size_type> b)
{
	return b.base() - i;
}

template <class it, class it2>
bool	operator == (const it &a, const it2 &b)
{
	return (a.base() == b.base());
}

template <class it, class it2>
bool	operator != (const it &a, const it2 &b)
{
	return (a.base() != b.base());
}

template <class it, class it2>
bool	operator < (const it &a, const it2 &b)
{
	return (a.base() < b.base());
}

template <class it, class it2>
bool	operator > (const it &a, const it2 &b)
{
	return (a.base() > b.base());
}

template <class it, class it2>
bool	operator >= (const it &a, const it2 &b)
{
	return (a.base() >= b.base());
}

template <class it, class it2>
bool	operator <= (const it &a, const it2 &b)
{
	return (a.base() <= b.base());
}

}

#endif