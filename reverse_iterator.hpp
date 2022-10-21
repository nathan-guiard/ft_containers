/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:16:10 by nguiard           #+#    #+#             */
/*   Updated: 2022/10/21 18:21:19 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR
#define FT_REVERSE_ITERATOR

namespace ft
{
	template<typename _Iterator>
    class reverse_iterator : public iterator
			<typename iterator_traits<_Iterator>::iterator_category,
			typename iterator_traits<_Iterator>::value_type,
			typename iterator_traits<_Iterator>::difference_type,
			typename iterator_traits<_Iterator>::pointer,
			typename iterator_traits<_Iterator>::reference>
	{

	};
}

#endif