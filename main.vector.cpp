/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:07:06 by abaur             #+#    #+#             */
/*   Updated: 2021/04/27 19:55:22 by abaur            ###   ########.fr       */
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

extern int	main()
{
	TestConstructors();
}
