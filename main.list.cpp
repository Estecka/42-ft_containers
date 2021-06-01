/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/06/01 14:20:28 by abaur            ###   ########.fr       */
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
static void	TestPushPop(){
	NS::list<int>	ls;
	ls.push_back (0); dump(ls);
	ls.push_back (1); dump(ls);
	ls.push_front(2); dump(ls);
	ls.push_front(3); dump(ls);
	ls.pop_back  () ; dump(ls);
	ls.pop_front () ; dump(ls);
	ls.push_back (4); dump(ls);
	ls.push_front(5); dump(ls);
}
static void	TestInsert(){
	NS::list<int>	ls(2, 0);
	ls.insert(ls.begin(), 2); dump(ls);
	ls.insert(ls.end(),   1); dump(ls);
	ls.insert(ls.begin(), 2, 2); dump(ls);
	ls.insert(ls.end(),   3, 3); dump(ls);
	ls.insert(ls.begin(), g_digits+8, g_digits+10); dump(ls);
	ls.insert(ls.end(),   g_digits+5, g_digits+ 8); dump(ls);
}
static void	TestErase(){
	NS::list<int>	ls;
	ls.assign(g_digits, g_digits+10);
	ls.erase(  ls.begin());	dump(ls);
	ls.erase(++ls.begin());	dump(ls);
	ls.erase(--ls.end());	dump(ls);
	//ls.erase(  ls.end());	dump(ls); // Crashes in the std, so cannot be tested.

	ls.erase(++ls.begin(), --ls.end());	dump(ls);
	ls.erase(++ls.begin(), --ls.end());	dump(ls);
	ls.erase(  ls.begin(),   ls.end());	dump(ls);
}
static void	TestSwap(){
	NS::list<int> a, b;

	a.assign(g_digits, g_digits+10);
	b.assign(a.rbegin(), a.rend());
	dump(a); dump(b);

	a.swap(b);
	dump(a); dump(b);
	b.swap(a);
	dump(a); dump(b);
	swap(a, b);
	dump(a); dump(b);
}
static void	TestModifiers(){
	TestAssign();
	TestPushPop();
	TestInsert();
	TestErase();
	TestSwap();
}

extern int	main() {
	TestConstructors();
	TestIterators();
	TestCapacity();
	TestAccess();
	TestModifiers();
}
