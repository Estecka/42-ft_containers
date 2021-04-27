/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:07:06 by abaur             #+#    #+#             */
/*   Updated: 2021/04/27 21:23:28 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "vector.hpp"
#include <vector>

#include "dump.hpp"

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

	// for (NS::vector<int>::const_reverse_iterator it=cdecimals.rbegin(); it<cdecimals.rend(); it++)
	// 	std::cout << *it;
	// std::cout << std::endl;
}

extern int	main()
{
	TestConstructors();
	TestIterators();
}
