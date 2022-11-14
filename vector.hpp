
#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

namespace ft
{

template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
	typedef	T							value_type;
	typedef	Allocator					allocator_type;
	typedef std::size_t					size_type;
	typedef	std::ptrdiff_t				difference_type;
	typedef	value_type &				reference;
	typedef const reference				const_reference;
	typedef	Allocator::pointer			pointer;
	typedef	Allocator::const_pointer	const_pointer;
	//typedef	iterator;
	//typedef	const_iterator
	//typedef	reverse_iterator
	//typedef	reverse_const_iterator

	vector();
	explicit vector(const Allocator &alloc);
	explicit vector(size_type count, const T &value,
					const Allocator &alloc = Allocator());
	explicit vector(size_type count);

	template <class InputIt>
	vector(InputIt first, InputIt last, const Allocator &alloc = Allocator());
	vector(const vector &other);
	~vector();

	vector &operator = (const vector &other);
	void	assign(size_type count, const T &value);

	template <class InputIt>
	void	assign(InputIt first, InputIt last);
	
	allocator_type	get_allocator()	const;
	
	reference		at(size_type pos);
	const_reference	at(size_type pos);

};
	
}

#endif
