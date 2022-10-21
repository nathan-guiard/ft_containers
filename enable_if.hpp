/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:26:53 by nguiard           #+#    #+#             */
/*   Updated: 2022/10/21 18:32:28 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENABLE_IF_HPP
#define FT_ENABLE_IF_HPP

#include <type_traits>

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T>
{
	typedef T	type;
};

#endif