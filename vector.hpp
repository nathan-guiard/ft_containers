/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:58:41 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/21 21:56:19 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include	<memory>
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

	vector(): _tab(0), _alloc(Allocator()), _size(0), _allocated(0) {}
	explicit vector(const Allocator &alloc):
		_tab(), _alloc(Allocator()),
		_size(0), _allocated(0)
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
		_allocated = count;
	}
	explicit vector(size_type count): _alloc()
	{
		size_type	i = 0;
		value_type	a = value_type();

		_tab = _alloc.allocate(count);
		for (; i != count; i++)
			_alloc.construct(_tab + i, a);
		_size = count;
		_allocated = count;
	}
	~vector() {clear();}

	template <class InputIt>
	vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
		typename enable_if<!is_integral<InputIt>::value, InputIt>::type * = NULL):
		_size(0)
	{
		_allocated = 0;
		_tab = 0;
		_alloc = alloc;
		for (; first != last; ++first)
		{
			push_back(*first); // a changer par insert
		}
	}
	vector(const vector &other): _alloc(other._alloc), _size(other._size)
	{
		_tab = _alloc.allocate(other._allocated);
		for (size_type i = 0; i != _size; i++)
			_alloc.construct(_tab + i, other._tab[i]);
		_allocated = other._allocated;
	}

	vector &operator = (const vector &other)
	{
		_alloc.deallocate(_tab, _allocated);
		_size = other._size;
		_tab = _alloc.allocate(other._allocated);
		_allocated = other._allocated;
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
	void	assign(InputIt first, InputIt last,
		typename enable_if<!is_integral<InputIt>::value, InputIt>::type * = NULL)
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
	size_type	max_size()	const	{return _alloc.max_size();}

	void		reserve(size_type x)
	{
		if (capacity() >= x)
			return ;

		vector		tmp(*this);
		size_type	i = 0;

		clear();
		_tab = _alloc.allocate(x);
		_allocated = x;
		for (; i != tmp._size; i++)
			_alloc.construct(_tab + i, tmp._tab[i]);
		_size = tmp._size;
	}
	size_type	capacity()	const	{return _allocated;};

	/*	MODIFIERS	*/
	void	clear()
	{
		for (size_type i = 0; i != _size; i++)
			_alloc.destroy(&_tab[i]);
		if (_tab)
			_alloc.deallocate(_tab, _allocated);
		_size = 0;
		_allocated = 0;
		_tab = 0;
	}

	iterator	insert(const_iterator pos, const T &value)
	{
		vector		before((const_iterator)begin(), pos);
		vector		after(pos, (const_iterator)end());
		size_type	bf_size = before.size();
		size_type	af_size = after.size();
		size_type	new_size = bf_size + af_size + 1;

		if (new_size > _allocated)
		{
			size_type	i = 0;
			
			clear();
			_tab = _alloc.allocate(new_size);
			_size = new_size;
			_allocated = new_size;
			for(;i < bf_size; i++)
				_alloc.construct(&_tab[i], before[i]);
			_alloc.construct(&_tab[i], value);
			for(;i < new_size; i++)
				_alloc.construct(&_tab[i], after[i - bf_size - 1]);
		}
		else
		{
			size_type	i = _size;
		
			for(; i >= 0; i--)
				_alloc.destroy(&_tab[i]);
			for(;i < bf_size; i++)
				_alloc.construct(&_tab[i], before[i]);
			_alloc.construct(&_tab[i], value);
			for(;i < af_size; i++)
				_alloc.construct(&_tab[i], after[i]);
		}
		return iterator(_tab, bf_size);
	}
	iterator	insert(const_iterator pos, size_type count, const T &value)
	{
		vector		before((const_iterator)begin(), pos);
		vector		between(count, value);
		vector		after(pos, (const_iterator)end());
		size_type	bf_size = before.size();
		size_type	bw_size = between.size();
		size_type	af_size = after.size();
		size_type	new_size = before.size() + between.size() + after.size();

		if (!bw_size)
			return iterator(pos.base());

		if (new_size > _allocated)
		{
			size_type	i = 0;
			
			clear();
			_tab = _alloc.allocate(new_size);
			_size = new_size;
			_allocated = new_size;
			for(;i < bf_size; i++)
				_alloc.construct(&_tab[i], before[i]);
			for(;i < new_size - af_size; i++)
				_alloc.construct(&_tab[i], between[i - bf_size]);
			for(;i < new_size; i++)
				_alloc.construct(&_tab[i], after[i - bf_size - bw_size]);
		}
		else
		{
			size_type	i = _size;
		
			for(; i >= 0; i--)
				_alloc.destroy(&_tab[i]);
			for(;i < bf_size; i++)
				_alloc.construct(&_tab[i], before[i]);
			for(;i < new_size - af_size; i++)
				_alloc.construct(&_tab[i], between[i - bf_size]);
			for(;i < new_size; i++)
				_alloc.construct(&_tab[i], after[i - bf_size - bw_size]);
		}
		return iterator(_tab, bf_size);
	}

	/**
	 * @brief Insere des elements avant pos grace a une range d'iterateurs.
	 * Si la size finale est plus grande que capacity(), invalide tous les
	 * iterateurs
	 * 
	 * @tparam It 		iterateurs pour la range
	 * @param pos 		iterateur "curseur" qui indique la position de
	 * 						l'insertion
	 * @param first 	debut de la range
	 * @param last 		fin de la range
	 * @return iterator premier element ajoute ou pos si rien n'a ete ajoute
	 */
	template <class It>
	iterator	insert(const_iterator pos, It first, It last,
		typename enable_if<!is_integral<It>::value, It>::type * = NULL)
	{
		vector		before((const_iterator)begin(), pos);
		vector		between(first, last);
		vector		after(pos, (const_iterator)end());
		size_type	bf_size = before.size();
		size_type	bw_size = between.size();
		size_type	af_size = after.size();
		size_type	new_size = before.size() + between.size() + after.size();

		if (first == last)
			return iterator(pos.base());

		if (new_size > _allocated)
		{
			size_type	i = 0;
			
			clear();
			_tab = _alloc.allocate(new_size);
			_size = new_size;
			_allocated = new_size;
			for(;i < bf_size; i++)
				_alloc.construct(&_tab[i], before[i]);
			for(;i < new_size - af_size; i++)
				_alloc.construct(&_tab[i], between[i - bf_size]);
			for(;i < new_size; i++)
				_alloc.construct(&_tab[i], after[i - bf_size - bw_size]);
		}
		else
		{
			size_type	i = _size;
		
			for(; i >= 0; i--)
				_alloc.destroy(&_tab[i]);
			for(;i < bf_size; i++)
				_alloc.construct(&_tab[i], before[i]);
			for(;i < new_size - af_size; i++)
				_alloc.construct(&_tab[i], between[i - bf_size]);
			for(;i < new_size; i++)
				_alloc.construct(&_tab[i], after[i - bf_size - bw_size]);
		}
		return iterator(_tab, before.size());
	}

	iterator	erase(iterator pos);
	iterator	erase(iterator first, iterator last);

	void	push_back(const T &value)
	{
		if (_size == 0)
		{
			_tab = _alloc.allocate(1);
			_alloc.construct(_tab, value);
			_size = 1;
			_allocated = 1;
		}
		else if (_allocated < _size + 1)
		{
			vector		tmp(*this);
			size_type	i = 0;

			clear();
			_tab = _alloc.allocate(tmp._size * 2);
			_allocated = tmp._size * 2;
			for (; i != tmp._size; i++)
				_alloc.construct(_tab + i, tmp._tab[i]);
			_alloc.construct(_tab + i, value);
			_size = tmp._size + 1;
		}
		else
		{
			_alloc.construct(_tab + _size, value);
			_size++;
		}
	}

	void	pop_back()
	{
			if (_size && _tab)
				_alloc.destroy(&_tab[_size - 1]);
			_size--;
	}

	void	resize(size_type count, T value = T())
	{
		if (_size > count)
		{
			for (; _size != count;)
				_alloc.destroy(&_tab[_size--]);
		}
		else if (count <= _allocated)
		{
			for (; count != _size;)
				_alloc.construct(&_tab[count++], value);
		}
		else
		{
			vector tmp(*this);
			insert(begin(), tmp.begin(), tmp.end());
			insert(end(), count - _size, value);
		}
	}

	void	swap(vector &other)
	{
		T 			*save_tab = _tab;
		size_type	save_size = _size;
		size_type	save_allocated = _allocated;
		Allocator	save_allocator = _alloc;
	
		_tab = other._tab;
		_size = other._size;
		_allocated = other._allocated;
		_alloc = other._alloc;
	
		other._tab = save_tab;
		other._size = save_size;
		other._allocated = save_allocated;
		other._alloc = save_allocator;
	}

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
	size_type	_allocated;

	size_type	_next_pow(size_type x)
	{
		size_type	i = 1;

		if (x == 0)
			return 0;
		while (i < x)
			i *= 2;
		return i;
	}
};

}

#endif
