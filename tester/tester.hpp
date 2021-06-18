/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:22:48 by abaur             #+#    #+#             */
/*   Updated: 2021/06/18 16:25:08 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include <typeinfo>
#include <iostream>

#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"

static const int	g_digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static inline void	log(const char* str) {
	std::cout << str << std::endl;
};

template<typename Container>
void	dump(const Container& c){
	std::cout << "[" << c.size() << "]{ ";
	for (typename Container::const_iterator it=c.begin(); it!=c.end(); it++)
	{
		std::cout << *it;
		if (it != --c.end())
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
}

template<typename IT>
void	dump(IT begin, IT end){
	std::cout << "{ ";
	for (IT it=begin; it!=end; it++)
		{
		if (it != begin)
			std::cout << ", ";
		std::cout << *it;
	}
	std::cout << " }" << std::endl;
}

#endif
