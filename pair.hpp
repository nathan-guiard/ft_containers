/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:00:33 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/08 14:12:46 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
#define	FT_PAIR_HPP

#include <utility> // a enlever

namespace ft
{

template <typename A, typename B>
class pair
{
public:
	pair(): first(), second() {};
	pair(const A& a, const B& b) : first(a), second(b) {};
	pair(const pair<A, B>&p) : first(p.first), second(p.second) {};
	
	pair	&operator = (const pair &copy)
	{
		first = copy.first;
		second = copy.second;
		return *this;
	}

	bool operator == (const pair<A, B>& p)	const	{return p.first == this->first && p.second == this->second;}
	bool operator != (const pair<A, B>& p)	const	{return !(this == p);}
	bool operator <	 (const pair<A, B>& p)	const	{return ((p.first < this->first) || !(this->first < p.first) && p.first < this->first);};
	bool operator <= (const pair<A, B>& p)	const	{return !(this > p);};
	bool operator >	 (const pair<A, B>& p)	const	{return ((p.first > this->first) || !(this->first > p.first) && p.first > this->first);};	bool operator >= (const pair<A, B>& p)	const	{return !(this < p);};

	A	first;
	B	second;
};



}//fin du namespace ft

#endif