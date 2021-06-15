/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:01:10 by abaur             #+#    #+#             */
/*   Updated: 2021/06/15 15:58:55 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "map.hpp"
#include <map>

#include "dump.hpp"
#include <typeinfo>

#include <iostream>

#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-variable"

static const int	g_digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static inline void	log(const char* str) { std::cout << str << std::endl; };
extern int	main() {
	NS::map<int, float> map;
}
