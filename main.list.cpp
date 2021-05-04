/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/05/04 17:21:40 by abaur            ###   ########.fr       */
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

	NS::list<int>	iter1(sized.begin(), sized.end());
	dump(iter1);
	NS::list<int>	iter2(g_digits, g_digits + 10);
	dump(iter2);
}

extern int	main() {
	TestConstructors();
}
