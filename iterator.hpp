/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:22:55 by nguiard           #+#    #+#             */
/*   Updated: 2022/10/21 18:25:15 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_ITERATOR_HPP
#define	FT_ITERATOR_HPP

#include <cstddef>

namespace ft
{
	template<typename Category, typename Tp, typename Distance = ptrdiff_t,
           typename Pointer = Tp*, typename Reference = Tp&>
    struct iterator
    {
      typedef Category  iterator_category;
      typedef Tp        value_type;
      typedef Distance  difference_type;
      typedef Pointer   pointer;
      typedef Reference reference;
    };
}

#endif