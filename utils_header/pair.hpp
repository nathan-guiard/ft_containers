/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:00:33 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/23 14:20:38 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
#define	FT_PAIR_HPP

namespace ft
{

template <typename A, typename B>
class pair
{
public:
	pair(): first(), second() {}
	pair(const A& a, const B& b) : first(a), second(b) {}
	pair(const pair<A, B>&p): first(p.first), second(p.second) {}
	~pair()	{}

	pair	&operator = (const pair &copy)
	{
		first = copy.first;
		second = copy.second;
		return *this;
	}

	A	first;
	B	second;
};

template<class A, class B>
inline bool operator != (const pair<A, B>& p, const pair<A, B>& q)
{
	return !(q == p);
}

template<class A, class B>
inline bool operator <	 (const pair<A, B>& p, const pair<A, B>& q)
{
	return ((p.first < q.first) || (!(q.first < p.first) && p.first < q.first));
}

template<class A, class B>
inline bool operator <= (const pair<A, B>& p, const pair<A, B>& q)
{
	return !(q > p);
};

template<class A, class B>
inline bool operator >	 (const pair<A, B>& p, const pair<A, B>& q)
{
	return ((p.first > q.first) || (!(q.first > p.first) && p.first > q.first));
};
		
template<class A, class B>
inline bool operator >= (const pair<A, B>& p, const pair<A, B>& q)	
{
	return !(q < p);
};

template<class A, class B>
inline bool operator == (const pair<A, B>& p, const pair<A, B>& q)
{
	return p.first == q.first && p.second == q.second;
}

template <typename A, typename B>
inline pair<A, B>	make_pair(const A &a, const B &b)
{
	return pair<A, B>(a, b);
}

} /* fin du namespace ft */

#endif