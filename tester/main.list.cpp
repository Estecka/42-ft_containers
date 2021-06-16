/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/06/10 17:39:57 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "list.hpp"
#include <list>

#include "dump.hpp"
#include <typeinfo>

#include <iostream>

#pragma clang diagnostic ignored "-Wunused-function"

static const int	g_digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static inline void	log(const char* str) { std::cout << str << std::endl; };

static void	TestConstructors() {
	log("Constructors");
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

	iter1 = defaut;
	dump(iter1);
	iter1 = iter2;
	dump(iter1);
	iter1 = sized;
	dump(iter1);
}

static void	TestIterators(){
	log("Iterators");
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
	log("Capacity");
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
	log("Access");
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
	log("Assign");
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
	log("Push/Pop");
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
	log("insert");
	NS::list<int>	ls(2, 0);
	ls.insert(ls.begin(), 2); dump(ls);
	ls.insert(ls.end(),   1); dump(ls);
	ls.insert(ls.begin(), 2, 2); dump(ls);
	ls.insert(ls.end(),   3, 3); dump(ls);
	ls.insert(ls.begin(), g_digits+8, g_digits+10); dump(ls);
	ls.insert(ls.end(),   g_digits+5, g_digits+ 8); dump(ls);

	ls.clear();
	ls.insert(ls.end(), 3);	dump(ls);
	ls.clear();
	ls.insert(ls.end(), 4, 5);	dump(ls);
	ls.clear();
	ls.insert(ls.end(), g_digits, g_digits+10);	dump(ls);
}
static void	TestErase(){
	log("Erase");
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
	log("Swap");
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
static void	TestResize(){
	log("Resize");
	NS::list<int> ls(g_digits, g_digits+10);

	ls.resize(15);    	dump(ls);
	ls.resize(20, 20);	dump(ls);
	ls.resize(18, 30);	dump(ls);
}
static void	TestClear(){
	log("Clear");
	NS::list<int> ls(g_digits, g_digits+8);

	dump(ls); ls.clear();
	dump(ls); ls.assign(g_digits+2, g_digits+7);
	dump(ls); ls.clear();
	dump(ls); ls.resize(10, 20);
	dump(ls); ls.clear();
}
static void	TestModifiers(){
	TestAssign();
	TestPushPop();
	TestInsert();
	TestErase();
	TestSwap();
	TestResize();
	TestClear();
}

static void TestSplice() {
	log("Splice");
	NS::list<int>	src;
	NS::list<int>	dst;

	src.assign(g_digits, g_digits+2);
	dst.splice(dst.end(), src);
	dump(src); dump(dst);

	dst.clear();
	src.assign(g_digits, g_digits+1);
	dst.splice(dst.end(), src);
	dump(src); dump(dst);

	src.assign(g_digits+1, g_digits+3);
	dst.splice(dst.begin(), src);
	dump(src); dump(dst);

	src.assign(g_digits, g_digits+2);
	dst.splice(++dst.begin(), src);
	dump(src); dump(dst);

	dst.clear();
	src.assign(g_digits, g_digits+6);
	dst.splice(dst.end(), src, ++src.begin(), --src.end());
	dump(src); dump(dst);
	dst.splice(dst.begin(), src, src.begin(), ++src.begin());
	dump(src); dump(dst);
	dst.splice(dst.begin(), src, src.begin());
	dump(src); dump(dst);

	dst.clear();
	src.assign(g_digits, g_digits+4);
	dst.splice(dst.end(), src, ++src.begin());
	dump(src); dump(dst);
	dst.splice(dst.end(), src, ++src.begin());
	dump(src); dump(dst);
	dst.splice(dst.begin(), src, --src.end());
	dump(src); dump(dst);
}
static bool	iseven(int i){
	return i % 2;
}
static void	TestRemove(){
	log("Remove");
	NS::list<int> ls(g_digits, g_digits+10);

	ls.remove(7);   	dump(ls);
	ls.push_back(6);	dump(ls);
	ls.remove(6);   	dump(ls);
	ls.remove(0);   	dump(ls);
	ls.remove_if(&iseven); dump(ls);
	ls.remove(2);   	dump(ls);
}
static bool	equateseven(int a, int b){
	return (a%2) == (b%2);
}
static void	TestUnique() {
	log("Unique");
	NS::list<int> ls;

	ls.assign(g_digits, g_digits+10);
	ls.insert(ls.end(), g_digits, g_digits+10);
	ls.unique();	dump(ls);
	ls.unique(&equateseven);	dump(ls);
	ls.push_back(4);
	ls.unique(&equateseven);	dump(ls);
	ls.push_front(3);
	ls.unique(&equateseven);	dump(ls);
}
static bool	reversesort(int a, int b) {
	return a > b;
}
static void	TestSort(){
	log("Sort");
	NS::list<int> ls;

	ls.assign(g_digits, g_digits+10);
	ls.reverse();
	ls.sort();
	dump(ls);
	ls.sort(&reversesort);
	dump(ls);
}
static void TestMerge() {
	log("Merge");
	NS::list<int> src;
	NS::list<int> dst;

	src.assign(g_digits+1, g_digits+7);
	dst.merge(src);
	dump(src); dump(dst);

	src.assign(g_digits, g_digits+10);
	dst.merge(src);
	dump(src); dump(dst);

	src.assign(g_digits+3, g_digits+6);
	src.sort(&reversesort);
	dst.sort(&reversesort);
	dst.merge(src);
	dump(src); dump(dst);
}
static void	TestReverse(){
	log("Reverse");
	NS::list<int> ls;

	ls.reverse();
	dump(ls);
	ls.push_back(0);
	ls.reverse();
	dump(ls);
	ls.assign(g_digits, g_digits+10);
	ls.reverse();
	dump(ls);
}
static void	TestOperations(){
	TestSplice();
	TestRemove();
	TestUnique();
	TestSort();
	TestMerge();
	TestReverse();
}

extern int	main() {
	TestConstructors();
	TestIterators();
	TestCapacity();
	TestAccess();
	TestModifiers();
	TestOperations();
}
