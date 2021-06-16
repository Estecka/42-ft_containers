/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:01:10 by abaur             #+#    #+#             */
/*   Updated: 2021/06/16 17:42:41 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "map.hpp"
#include <map>

// Required by function `dump` in order to work with maps.
template <typename K, typename V>
std::ostream&	operator<<(std::ostream& dst, const NS::pair<K,V>& src) {
	return dst << src.first << "=>" << src.second;
}

#include "dump.hpp"
#include <typeinfo>

#include <iostream>

#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-variable"

static const int	g_digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static inline void	log(const char* str) { std::cout << str << std::endl; };
extern int	main() {
	NS::map<int, float> map;

	map.insert(NS::pair<int, float>(5, 5.5f));
	map.insert(NS::pair<int, float>(8, 7.0f));
	map.insert(NS::pair<int, float>(1, 1.2f));
	map.insert(NS::pair<int, float>(6, 5.2f));
	map.insert(NS::pair<int, float>(2, 1.3f));
	dump(map);
}
