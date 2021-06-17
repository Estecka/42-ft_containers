/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:01:10 by abaur             #+#    #+#             */
/*   Updated: 2021/06/17 19:17:46 by abaur            ###   ########.fr       */
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

struct endless_pair_iterator
{
	int	index;
	NS::pair<int, float>	value;

	endless_pair_iterator(int index) {
		this->index = index;
		this->Update();
	}

	void Update() {
		this->value.first  = index;
		this->value.second = index + (index/2.0f);
	}

	NS::pair<int, float>&	operator* () { return this->value; }
	NS::pair<int, float>*	operator->() { return &**this; }
	endless_pair_iterator&	operator++() { this->index++; this->Update(); return *this; }
	endless_pair_iterator&	operator--() { this->index--; this->Update(); return *this; }
	endless_pair_iterator	operator++(int) { ++*this; return endless_pair_iterator(index-1); }
	endless_pair_iterator	operator--(int) { --*this; return endless_pair_iterator(index+1); }
	bool	operator==(const endless_pair_iterator& other) { return this->index == other.index; }
	bool	operator!=(const endless_pair_iterator& other) { return this->index != other.index; }
};

static void	TestConstructors(){
	NS::map<int, float>	defaut;
	dump(defaut);

	NS::map<int, float>	iterator(endless_pair_iterator(0), endless_pair_iterator(5));
	dump(iterator);

	NS::map<int, float>	copya(defaut);
	NS::map<int, float>	copyb(iterator);
	dump(copya);
	dump(copyb);
}

extern int	main() {
	TestConstructors();
}
