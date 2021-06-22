/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:01:10 by abaur             #+#    #+#             */
/*   Updated: 2021/06/22 17:54:20 by abaur            ###   ########.fr       */
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

typedef	NS::pair<int,float>	pairif;

struct endless_pair_iterator
{
	int	index;
	pairif	value;

	endless_pair_iterator(int index) {
		this->index = index;
		this->Update();
	}

	void Update() {
		this->value.first  = index;
		this->value.second = index + (index/2.0f);
	}

	pairif&	operator* () { return this->value; }
	pairif*	operator->() { return &**this; }
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

	NS::map<int, float>	equals;
	equals = defaut;
	dump(equals);
	equals = iterator;
	dump(equals);
}

static void	TestIterators(){
	NS::map<int, float>	map;
	const NS::map<int, float>&	cmap = map;
	map.insert(endless_pair_iterator(10), endless_pair_iterator(50));

	dump( map.begin(),  map.end());
	dump(cmap.begin(), cmap.end());
	dump( map.rbegin(),  map.rend());
	dump(cmap.rbegin(), cmap.rend());
}

static void	TestCapacity(){
	NS::map<int, float>	map;
	std::cout << map.empty() << map.size() << std::endl;

	map.insert(endless_pair_iterator(5), endless_pair_iterator(6));
	std::cout << map.empty() << map.size() << std::endl;
	
	map.insert(endless_pair_iterator(6), endless_pair_iterator(20));
	std::cout << map.empty() << map.size() << std::endl;

	for (int i=5; i<20; i++)
		std::cout << map[i] << ", ";
	std::cout << std::endl;

	map.clear();
	std::cout << map.empty() << map.size() << std::endl;

	map.max_size();

}

static void	TestModifiers(){
	NS::map<int,float>	map;

	NS::map<int,float>::iterator	five, seven, eight;

	map.insert(endless_pair_iterator(3), endless_pair_iterator(6));
	dump(map);

	five  = --map.end();
	eight = map.insert(pairif(8, 16)).first; 	dump(map);
	seven = map.insert(pairif(7, 4.5)).first;	dump(map);

	map.insert(five, pairif(6, 3.5));   	dump(map);
	map.insert(eight, pairif(9, 4.5));  	dump(map);
	map.insert(seven, pairif(10, 12.0));	dump(map);

	map.erase(9);    	dump(map);
	map.erase(seven);	dump(map);
	map.erase(five); 	dump(map);
	map.erase(1000); 	dump(map);

	map.erase(++map.begin(), --map.end());	dump(map);
	map.erase(  map.begin(),   map.end());	dump(map);
}

extern int	main() {
	TestConstructors();
	TestIterators();
	TestCapacity();
	TestModifiers();
}
