/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:58:41 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/21 09:51:01 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include	"utils"
#include	"vector_iterator.hpp"

namespace ft
{

template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
	typedef	T									value_type;
	typedef	Allocator							allocator_type;
	typedef std::size_t							size_type;
	typedef	std::ptrdiff_t						difference_type;
	typedef	value_type &						reference;
	typedef const value_type &					const_reference;
	typedef	typename Allocator::pointer			pointer;
	typedef	typename Allocator::const_pointer	const_pointer;

	typedef	ft::vector_iterator<T, size_type>		iterator;
	typedef	ft::const_vector_iterator<T, size_type>	const_iterator;
	typedef	ft::reverse_iterator<iterator>			reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	vector(): _tab(), _alloc(Allocator()), _size(0) {}
	explicit vector(const Allocator &alloc): _tab(), _alloc(Allocator()), _size(0)
	{
		_alloc = alloc;
	}
	explicit vector(size_type count, const T &value,
					const Allocator &alloc = Allocator())
	{
		size_type	i = 0;

		_alloc = alloc;
		_tab = _alloc.allocate(count);
		for (; i != count; i++)
			_alloc.construct(_tab + i, value);
		_size = count;
		_alloced_size = _size;
	}
	explicit vector(size_type count): _alloc()
	{
		size_type	i = 0;
		value_type	a = value_type();

		_tab = _alloc.allocate(count);
		for (; i != count; i++)
			_alloc.construct(_tab + i, a);
		_size = count;
		_alloced_size = count;
	}
	~vector() {if (_alloced_size) _alloc.deallocate(_tab, _alloced_size);}

	template <class InputIt>
	vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()):
		_size(0)
	{
		_alloc = alloc;
		for (; first != last; first++)
			push_back(*first); // a changer par insert
	}
	vector(const vector &other): _alloc(other._alloc), _size(other._size)
	{
		_tab = _alloc.allocate(_size);
		for (size_type i = 0; i != _size; i++)
			_alloc.construct(_tab + i, other._tab[i]);
		_alloced_size = _size;
	}

	vector &operator = (const vector &other)
	{
		_alloc.deallocate(_tab, _alloced_size);
		_size = other._size;
		_tab = _alloc.allocate(other._size);
		_alloced_size = other._size;
		for (size_type i = 0; i != _size; i++)
			_alloc.construct(_tab + i, other._tab[i]);
		return *this;
	}

	void	assign(size_type count, const T &value)
	{
		clear();

		for (size_type i = 0; i != count; i++)
			push_back(value);// a changer par insert
	}

	template <class InputIt>
	void	assign(InputIt first, InputIt last)
	{
		clear();
		
		for (size_type i = 0; first != last; i++, first++)
			push_back(*first);// a changer par insert
	}
	
	allocator_type	get_allocator()	const;
	
	/*	ELEMENT ACCES	*/
	reference		at(size_type pos)
	{
		if (_size < pos)
			throw (std::out_of_range("vector::at"));
		return _tab[pos];
	}
	const_reference	at(size_type pos)	const
	{
		if (_size < pos)
			throw (std::out_of_range("vector::at"));
		return _tab[pos];
	}

	reference		operator[](size_type pos)
	{
		return _tab[pos];
	}
	const_reference	operator[](size_type pos)	const
	{
		return _tab[pos];
	}

	reference			front()
	{
		return _tab[0];
	}
	const_reference		front()	const
	{
		return _tab[0];
	}

	reference			back()
	{
		return _tab[_size - 1];
	}
	const_reference		back()	const
	{
		return _tab[_size - 1];
	}

	T		*data()
	{
		return _tab;
	}
	const T	*data()	const
	{
		return _tab;
	}

	/*	ITERATORS	*/
	iterator		begin()			{return iterator(_tab, 0);}
	const_iterator	begin()	const	{return const_iterator(_tab, 0);}
	iterator		end()			{return iterator(_tab, _size);}
	const_iterator	end()	const	{return const_iterator(_tab, _size);}

	reverse_iterator		rbegin()
	{
		return reverse_iterator(iterator(_tab, _size));
	}
	const_reverse_iterator	rbegin()	const
	{
		return const_reverse_iterator(const_iterator(_tab, _size));
	}
	reverse_iterator		rend()
	{
		return reverse_iterator(iterator(_tab, 0));
	}
	const_reverse_iterator	rend()	const
	{
		return const_reverse_iterator(const_iterator(_tab, 0));
	}

	/*	CAPACITY	*/
	bool		empty()		const	{return (_size == 0 ? true : false);}
	size_type	size()		const	{return _size;}
	size_type	max_size()	const	{return _alloc.max_size() / sizeof(T);}
	void		reserve()	const;
	size_type	capacity()	const	{return _alloced_size - _size;};

	/*	MODIFIERS	*/
	void	clear()
	{
		_alloc.deallocate(_tab, _alloced_size);
		_size = 0;
		_alloced_size = 0;
	}

	iterator	insert(const_iterator pos, const T &value);
	iterator	insert(const_iterator pos, size_type count, const T &value);
	
	template <class It>
	iterator	insert(const_iterator pos, It first, It last);
	// {
		
	// }

	iterator	erase(iterator pos);
	iterator	erase(iterator first, iterator last);

	void	push_back(const T &value)
	{
		T *ptr;
	
		ptr = _alloc.allocate(++_size);
	
		for (size_type i = 0; i != _size - 1; i++)
		{
			_alloc.construct(ptr + i, _tab[i]);
			_alloc.destroy(_tab + i);
		}
		_alloc.construct(ptr + _size - 1, value);
		_alloc.deallocate(_tab, _size - 1);
		_tab = ptr;
	}
	void	pop_back();

	void	resize(size_type, T  value = T());
	void	resize(vector &other);

	bool	operator == (const vector &x)	const
	{
		return ft::equal(begin(), end(), x.begin());
	}

	bool	operator != (const vector &x)	const
	{
		return !(*this == x);
	}

	bool	operator <  (const vector &x)	const
	{
		return ft::lexicographical_compare(begin(), end(), x.begin(), x.end());
	}

	bool	operator <= (const vector &x)	const
	{
		return !(x < *this);
	}

	bool	operator >  (const vector &x)	const
	{
		return (x < *this);
	}

	bool	operator >= (const vector &x)	const
	{
		return !(*this < x);
	}
//A REMMETRE APRES
private:
	T			*_tab;
	Allocator	_alloc;
	size_type	_size;
	size_type	_alloced_size;
};

}

#endif
