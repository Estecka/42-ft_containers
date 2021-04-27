/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:07:06 by abaur             #+#    #+#             */
/*   Updated: 2021/04/27 19:26:55 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "vector.hpp"
#include <vector>

#include "dump.hpp"

extern int	main()
{
	NS::vector<int> decimals(10);
	for (int i=0; i<10; i++)
		decimals[i] = i;
	dump(decimals);
}
