/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:01:10 by abaur             #+#    #+#             */
/*   Updated: 2021/06/16 18:26:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>

// Required by function `dump` in order to work with maps.
template <typename K, typename V>
std::ostream&	operator<<(std::ostream& dst, const NS::pair<K,V>& src) {
	return dst << src.first << "=>" << src.second;
}

#include "tester.hpp"

extern int	main() {
	NS::map<int, float> map;

	map.insert(NS::pair<int, float>(5, 5.5f));
	map.insert(NS::pair<int, float>(8, 7.0f));
	map.insert(NS::pair<int, float>(1, 1.2f));
	map.insert(NS::pair<int, float>(6, 5.2f));
	map.insert(NS::pair<int, float>(2, 1.3f));
	dump(map);
}
