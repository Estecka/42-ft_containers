/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:05:43 by abaur             #+#    #+#             */
/*   Updated: 2021/04/27 20:43:55 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUMP_HPP
#define DUMP_HPP

#include <iostream>

template<typename Container>
void	dump(const Container& c){
	std::cout << "{ ";
	for (typename Container::const_iterator it=c.begin(); it<c.end(); it++)
	{
		std::cout << *it;
		if (it+1 < c.end())
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;
}

#endif
