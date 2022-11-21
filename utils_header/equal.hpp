/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:32:37 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/09 11:49:44 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EQUAL_HPP
#define	FT_EQUAL_HPP

#include <algorithm>

namespace ft
{

template <class it1, class it2>
bool equal(it1 f1, it1 e1, it2 f2)
{
	for (; f1 != e1; ++f1, ++f2)
		if (*f1 != *f2)
			return false;
	return true;
}

}

#endif