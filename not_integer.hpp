/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_integer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:39:01 by abaur             #+#    #+#             */
/*   Updated: 2021/05/06 16:44:49 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __IS_INTEGER_HPP
#define __IS_INTEGER_HPP

#include <memory>

#define NOT_INTEGER(IT)	typename ft::not_integer<IT>::_true

namespace ft
{
	template <typename T>
	struct not_integer {
		typedef char	_true;
	};

	template<> struct not_integer<bool> {};
	template<> struct not_integer<char> {};
	template<> struct not_integer<short> {};
	template<> struct not_integer<int> {};
	template<> struct not_integer<long> {};
	template<> struct not_integer<long long> {};
	template<> struct not_integer<signed char> {};
	template<> struct not_integer<unsigned short> {};
	template<> struct not_integer<unsigned int> {};
	template<> struct not_integer<unsigned long> {};
	template<> struct not_integer<unsigned long long> {};
}

#endif
