/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/05/30 10:10:44 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "list.hpp"
#include <list>

#include "dump.hpp"
#include <typeinfo>

static const int	g_digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static void	TestConstructors() {
	NS::list<int> defaut;
	dump(defaut);

	NS::list<int> sized(10);
	dump(sized);
	for (int i=0; i<10; i++)
		sized.push_back(i);
	dump(sized);

	NS::list<int> copy(sized);
	dump(copy);

	NS::list<int>	valued(10, 5);
	dump(valued);

	NS::list<int>	iter1(sized.begin(), sized.end());
	dump(iter1);
	NS::list<int>	iter2(g_digits, g_digits + 10);
	dump(iter2);
}

static void	TestIterators(){
	NS::list<int> decimals(g_digits, g_digits+3);
	const NS::list<int>& cdecimals = decimals;

	for (NS::list<int>::iterator it=decimals.begin(); it!=decimals.end(); it++)
		std::cout << *it;
	std::cout << std::endl;

	for (NS::list<int>::const_iterator it=cdecimals.begin(); it!=cdecimals.end(); it++)
		std::cout << *it;
	std::cout << std::endl;

	for (NS::list<int>::reverse_iterator it=decimals.rbegin(); it!=decimals.rend(); it++)
		std::cout << *it;
	std::cout << std::endl;

	for (NS::list<int>::const_reverse_iterator it=cdecimals.rbegin(); it!=cdecimals.rend(); it++)
		std::cout << *it;
	std::cout << std::endl;
}

static void	TestCapacity(){
	NS::list<int> ls;

	std::cout << ls.max_size() << std::endl;
	std::cout << ls.size() << std::endl;
	std::cout << ls.empty() << std::endl;

	for (int i=0; i<10; i++) {
		ls.push_back(1);
		std::cout << ls.empty() << ls.size() << std::endl;
	}
	dump(ls);
}

static void	TestAccess(){
	NS::list<int> ls;
	for (int i=0; i<10; i++) {
		rand() % 2 ?
			ls.push_back (rand()%100):
			ls.push_front(rand()%100);
		std::cout << ls.front() << ls.back() << std::endl;
		dump(ls);
	}
}

static void	TestAssign(){
	NS::list<int> ass1;
	NS::list<int> ass2;
	dump(ass1);
	dump(ass2);
	ass1.assign(3, 5);
	ass2.assign(12, 6);
	dump(ass1);
	dump(ass2);
	ass1.assign(g_digits+1, g_digits+6);
	ass2.assign(++ass1.begin(), --ass1.end());
	dump(ass1);
	dump(ass2);
	ass1.assign(g_digits+1, g_digits+3);
	ass2.assign(g_digits, g_digits+10);
	dump(ass1);
	dump(ass2);

	NS::list<std::string> ass3;
	ass3.assign( 5, "abc"); dump(ass3);
	ass3.assign(10, "def"); dump(ass3);
	ass3.assign( 2, "ghi"); dump(ass3);
}
static void	TestModifiers(){
	TestAssign();
}

extern int	main() {
	TestConstructors();
	TestIterators();
	TestCapacity();
	TestAccess();
	TestModifiers();
}
