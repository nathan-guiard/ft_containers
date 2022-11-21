/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:37:45 by nguiard           #+#    #+#             */
/*   Updated: 2022/11/21 17:26:10 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_IS_INTEGRAL_HPP
#define	FT_IS_INTEGRAL_HPP


namespace ft
{

template <class T>
struct is_integral	{ static const bool value = false; };

template <>
struct is_integral<int>				{ static const bool value = true; };

template <>
struct is_integral<unsigned int>	{ static const bool value = true; };

template <>
struct is_integral<bool>			{ static const bool value = true; };

template <>
struct is_integral<char>			{ static const bool value = true; };

template <>
struct is_integral<unsigned char>	{ static const bool value = true; };

template <>
struct is_integral<long>			{ static const bool value = true; };

template <>
struct is_integral<unsigned long>	{ static const bool value = true; };

template <>
struct is_integral<float>			{ static const bool value = true; };

template <class T>
struct is_integral<const T>		: is_integral<T> {};

template <class T>
struct is_integral<volatile T>	: is_integral<T> {};

}

#endif