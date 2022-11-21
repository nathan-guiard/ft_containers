/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:26:53 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/21 17:18:48 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENABLE_IF_HPP
#define FT_ENABLE_IF_HPP

#include	"is_integral.hpp"

namespace ft
{
template <bool, typename T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };
}

#endif