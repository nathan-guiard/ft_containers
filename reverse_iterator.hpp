/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:16:10 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/04 13:43:06 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR
#define FT_REVERSE_ITERATOR

#include <cstddef>

namespace ft
{

template<typename Category,
	typename Tp,
	typename Distance = std::ptrdiff_t,
	typename Pointer = Tp*,
	typename Reference = Tp&>
struct reverse_iterator
{
	typedef Category	iterator_category;
	typedef Tp			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
}; // fin de la struct reverse_iterator

} // fin namespace ft

#endif