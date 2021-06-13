/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:15:00 by abaur             #+#    #+#             */
/*   Updated: 2021/06/13 17:15:55 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <typename KEY, typename VAL>
	struct pair {
		KEY	first;
		VAL	second;

		pair() : first(), second() {}
		pair(const KEY& _first, const VAL& _value) : first(_first), second(_value) {}
		pair(const pair& other) : first(other.first), second(other.second) {}
		pair&	operator=(const pair& other) { first=other.first; second=other.second; }
		~pair(){}
	};
}

#endif
