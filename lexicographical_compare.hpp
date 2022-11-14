/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:11:55 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/14 02:31:32 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXICOGRAPHCAL_COMPARE_HPP
#define FT_LEXICOGRAPHCAL_COMPARE_HPP

namespace ft
{

template <class ita, class itb>
inline bool lexicographical_compare(ita f1, ita e1, itb f2, itb e2)
{
	for (; f1 != e1 && f2 != e2; ++f1, ++f2)
	{
		if (f1 < f2)
			return true;
		if (f2 < f1)
			return false;
	}
	return (f1 == e1 && f2 != e2);
}

}//fin du namespace ft

#endif