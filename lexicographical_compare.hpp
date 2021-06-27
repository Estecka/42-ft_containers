/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:18:45 by abaur             #+#    #+#             */
/*   Updated: 2021/06/27 15:29:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

#include <iostream>

namespace ft
{

	template <class Container>
	short	lexicograph_compare(const Container& a, const Container& b){
		typename Container::const_iterator
			ait=a.begin(), 
			bit=b.begin();

		while (true) {
			if (ait == a.end())
				return (bit == b.end()) ? 0 : -1;
			if (bit == b.end())
				return 1;
			if (*ait < *bit)
				return -1;
			if (*bit < *ait)
				return 1;
			ait++, bit++;
		}
	}

	short	lexicograph_compare(const char*	a, const char* b) {
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

	short	lexicograph_compare(const std::string& a, const std::string& b) {
		return lexicograph_compare(a.c_str(), b.c_str());
	}

}

#endif
