/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:18:45 by abaur             #+#    #+#             */
/*   Updated: 2021/06/26 15:32:11 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

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

}

#endif
