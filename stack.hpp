
#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <cstddef>
#include <deque>

namespace ft
{

template <class T, class Container = std::deque<T> >
class stack
{
public:
	typedef	Container							container_type;
	typedef	typename Container::size_type		size_type;
	typedef	typename Container::value_type		value_type;
	typedef	typename Container::reference		reference;
	typedef	typename Container::const_reference	const_reference;

	explicit stack(const Container &c = Container()) {}
	stack(const stack &other) {}
	~stack() {}

	stack	&operator = (const stack &other) {}

	/*	ELEMENT ACCES	*/
	reference top();
	const_reference	top()	const;

	/*	CAPACITY		*/
	bool		empty()	const;
	size_type	size()	const;

	/*	MODIFIERS		*/
	void	push(const value_type &value);
	void	pop();

protected:
	Container	c;
}; // fin de la class stack

template<class T, class Container>
bool operator == (const stack<T, Container> &a, const stack<T, Container> &b);

template<class T, class Container>
bool operator != (const stack<T, Container> &a, const stack<T, Container> &b);

template<class T, class Container>
bool operator <  (const stack<T, Container> &a, const stack<T, Container> &b);

template<class T, class Container>
bool operator <= (const stack<T, Container> &a, const stack<T, Container> &b);

template<class T, class Container>
bool operator >  (const stack<T, Container> &a, const stack<T, Container> &b);

template<class T, class Container>
bool operator <= (const stack<T, Container> &a, const stack<T, Container> &b);

} //fin de lu namespace ft

#endif
