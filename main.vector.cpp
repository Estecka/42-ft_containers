/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:07:06 by abaur             #+#    #+#             */
/*   Updated: 2021/04/29 19:57:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "vector.hpp"
#include <vector>

#include "dump.hpp"
#include <typeinfo>

static const int	g_digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static void	TestConstructors() {
	NS::vector<int> defaut;
	dump(defaut);

	NS::vector<int> sized(10);
	dump(sized);
	for (int i=0; i<10; i++)
		sized[i] = i;
	dump(sized);

	NS::vector<int> copy(sized);
	dump(copy);

	NS::vector<int>	iter1(sized.begin(), sized.end());
	dump(iter1);
	NS::vector<int>	iter2(g_digits, g_digits + 10);
	dump(iter2);
}

static void	TestIterators(){
	NS::vector<int> decimals(g_digits, g_digits+3);
	const NS::vector<int>& cdecimals = decimals;

	for (NS::vector<int>::iterator it=decimals.begin(); it<decimals.end(); it++)
		std::cout << *it;
	std::cout << std::endl;

	for (NS::vector<int>::const_iterator it=cdecimals.begin(); it<cdecimals.end(); it++)
		std::cout << *it;
	std::cout << std::endl;

	for (NS::vector<int>::reverse_iterator it=decimals.rbegin(); it<decimals.rend(); it++)
		std::cout << *it;
	std::cout << std::endl;

	for (NS::vector<int>::const_reverse_iterator it=cdecimals.rbegin(); it<cdecimals.rend(); it++)
		std::cout << *it;
	std::cout << std::endl;
}

static void	TestCapacity(){
	NS::vector<int> vec;

	std::cout << vec.max_size() << std::endl;
	std::cout << vec.size() << std::endl;
	vec.reserve(12);
	std::cout << vec.capacity() << std::endl;
	for (int i=0; i<10; i++)
		vec.push_back(1);
	dump(vec);
	std::cout << vec.capacity() << std::endl;
	vec.empty();
	dump(vec);
	std::cout << vec.capacity() << std::endl;
	vec.resize(5, 6);
	dump(vec);
	std::cout << vec.capacity() << std::endl;
	for (int i=0; i<10; i++)
		vec.push_back(2*i);
	dump(vec);
	std::cout << vec.capacity() << std::endl;
}

static void	TestAccess(){
	NS::vector<int> vec;
	const NS::vector<int>& cvec = vec;

	vec.reserve(20);
	for (int i=0; i<5; i++){
		vec[i] = i;
		std::cout << cvec[i];
	}
	std::cout << std::endl;
	dump(vec);

	vec.resize(10, 0);
	for (int i=5; i<10; i++) {
		vec.at(i) = i;
		std::cout << cvec.at(i);
	}
	std::cout << std::endl;
	dump(vec);

	vec[15] = 10;
	try { vec.at(-1); }
	catch (const std::out_of_range& e) {
		std::cout <<  typeid(e).name() << std::endl;
	}
	try { cvec.at(11); }
	catch (const std::out_of_range& e) {
		std::cout << typeid(e).name() << std::endl;
	}
	try { vec.at(-1); }
	catch (const std::out_of_range& e) {
		std::cout <<  typeid(e).name() << std::endl;
	}
	try { cvec.at(11); }
	catch (const std::out_of_range& e) {
		std::cout << typeid(e).name() << std::endl;
	}

	std::cout <<  vec.back() <<  vec.front() << std::endl;
	std::cout << cvec.back() << cvec.front() << std::endl;
}

static void	TestModifiers(){
	NS::vector<int> vec;

	vec.assign(10, 5);
	dump(vec);
	vec.assign(g_digits, g_digits+10);
	dump(vec);

	vec.push_back(-1);
	vec.push_back(-2);
	dump(vec);
	vec.pop_back();
	dump(vec);

	vec.insert(vec.begin()+3, 10);
	dump(vec);
	vec.insert(vec.begin()+5, 5, 11);
	dump(vec);
	vec.insert(vec.begin()+8, g_digits+2, g_digits+9);
	dump(vec);

	vec.erase(vec.begin()+2);
	dump(vec);
	vec.erase(vec.begin()+5, vec.end()-3);
	dump(vec);

	NS::vector<int>	a;
	NS::vector<int>	b;
	a.assign(3, 6);
	b.assign(10, 12);
	dump(a);
	dump(b);
	std::cout << b.capacity() << std::endl << a.capacity() << std::endl;
	NS::swap(a, b);
	dump(a);
	dump(b);
	std::cout << b.capacity() << std::endl << a.capacity() << std::endl;
	b.swap(a);
	dump(a);
	dump(b);
	std::cout << b.capacity() << std::endl << a.capacity() << std::endl;

	vec.clear();
	a.clear();
	b.clear();
	dump(vec);
	dump(a);
	dump(b);
}


extern int	main()
{
	TestConstructors();
	TestIterators();
	TestCapacity();
	TestAccess();
	TestModifiers();
}
