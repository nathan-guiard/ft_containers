/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:22:55 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/16 11:10:03 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_ITERATOR_HPP
#define	FT_ITERATOR_HPP

#include <cstddef>

namespace ft
{

template<typename Category,
	typename Tp,
	typename Distance = std::ptrdiff_t,
	typename Pointer = Tp*,
	typename Reference = Tp& >
struct iterator_traits
{
public:
	typedef Category	iterator_category;
	typedef Tp			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
}; // fin de la struct iterator

} // fin namespace ft

#endif