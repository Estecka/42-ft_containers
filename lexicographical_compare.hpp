/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:18:45 by abaur             #+#    #+#             */
/*   Updated: 2021/07/12 16:51:19 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

#include "less.hpp"

#include <iostream>

namespace ft
{
	template<typename T>
	struct less;

	template <class Container>
	short	lexicograph_compare(const Container& a, const Container& b){
		ft::less<typename Container::value_type>	less;
		typename Container::const_iterator
			ait=a.begin(), 
			bit=b.begin();

		while (true) {
			if (ait == a.end())
				return (bit == b.end()) ? 0 : -1;
			if (bit == b.end())
				return 1;
			if (less(*ait, *bit))
				return -1;
			if (less(*bit, *ait))
				return 1;
			ait++, bit++;
		}
	}

	template <>
	short	lexicograph_compare(const std::string& stra, const std::string& strb) {
		const char*	a = stra.c_str();
		const char*	b = strb.c_str();

		if (!a)
			return (!b) ? 0 : -1;
		if (!b)
			return 1;

		while (true) {
			if (!*a)
				return (!*b) ? 0 : -1;
			if (!*b)
				return 1;
			if (*a < *b)
				return -1;
			if (*b < *a)
				return 1;
			a++, b++;
		}
	}

}

#endif
